/*
*	FILE		  : BitmapImage.cpp
*   PROJECT		  :	GAS - Assignment 1
*   PROGRAMMER	  : Wes Martin
*	FIRST VERSION : 12/2/18
*	DESCRIPTION	  : This file contains the code needed to generate bitmap images to be used
*				  : in the set invaders game. This file is primarily provided by Russ Foubert,
*				  : with chroma keying added myself.
*/

/****************************************************
The concept behind this class is that it will be passed
a filename and graphics object/rendertarget, then, will
proceed to create the needed WIC components to read,
decode, and then encode the bitmap file from disk into
a compatible D2D bitmap.

We need this approach to be able to address pretty much
any bitmap from disk/resources into the game and use it
within Directx (D2D specifically for now)

-Russ Foubert
*******************************************************/

#include "BitmapImage.h"
#include "Common.h"

/**
 * \brief
 * \param inFilename The file name that the bitmap will be pulled from
 * \param gfx The graphics handler to draw to the screen
 * \param doChroma Indicates if the picture should be chroma keyed
 */
BitmapImage::BitmapImage(char* inFilename, Graphics* gfx, bool doChroma = false)
{
	wchar_t* filename = (wchar_t*)malloc(kMAX_FILE_NAME);
	mbstowcs(filename, inFilename, kMAX_FILE_NAME);

	this->gfx = gfx; //save the gfx parameter for later
	bmp = nullptr; //This needs to be NULL to start off
	HRESULT hr;

	wicFactory = nullptr;
	wicDecoder = nullptr;
	wicFrame = nullptr;
	wicConverter = nullptr;
	pILock = nullptr;
	pIBitmap = nullptr;

	//Step 1: Create a WIC Factory
	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		nullptr,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		(LPVOID*)&wicFactory);

	//Step 2: Create a Decoder to read file into a WIC Bitmap
	hr = wicFactory->CreateDecoderFromFilename(
		filename,
		nullptr,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&wicDecoder);

	//Step 3: Read a 'frame'. We're really just moving the whole image into a frame here
	hr = wicDecoder->GetFrame(0, &wicFrame);


	if (doChroma)
	{
		DoChroma();
	}
	else
	{
		//Step 4: Create a WIC Converter
		hr = wicFactory->CreateFormatConverter(&wicConverter);

		//Step 5: Configure the Converter
		hr = wicConverter->Initialize(
			wicFrame,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			nullptr,
			kDEFAULT,
			WICBitmapPaletteTypeCustom
		);

	}

	//Step 6: Create the D2D Bitmap! Finally!
	gfx->GetRenderTarget()->CreateBitmapFromWicBitmap(
		wicConverter,
		nullptr,
		&bmp
	);
}



/**
 * \brief Destructor, frees all objects that were used
 */
BitmapImage::~BitmapImage()
{
	if (wicFactory) wicFactory->Release();
	if (wicDecoder) wicDecoder->Release();
	if (wicFrame) wicFrame->Release();
	if (wicConverter) wicConverter->Release();
	if (pILock) pILock->Release();;
	if (pIBitmap) pIBitmap->Release();
	if (bmp) bmp->Release();
}



/**
 * \brief Draw a bitmap on screen, covering the entire target area
 */
void BitmapImage::FullScreenDraw()
{
	gfx->GetRenderTarget()->DrawBitmap(
		bmp,
		D2D1::RectF(kDEFAULT, kDEFAULT,
			gfx->GetRenderTarget()->GetSize().width, gfx->GetRenderTarget()->GetSize().height),
		kOPAQUE,
		D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		D2D1::RectF(kDEFAULT, kDEFAULT, bmp->GetSize().width, bmp->GetSize().height)
	);
}



/**
 * \brief Draw a bitmap at a specific location on screen with a specific size
 * \param topLeftX The top left coordinate x value
 * \param topLeftY The top left coordinate y value
 * \param w The desired width of the image
 * \param h The desired height of the image
 */
void BitmapImage::Draw(float topLeftX, float topLeftY, float w, float h)
{
	//D2D1::Matrix3x2F rot = D2D1::Matrix3x2F::Rotation((rand() % 360), D2D1::Point2F(topLeftX + w / 2, topLeftY + h / 2));
	//gfx->GetRenderTarget()->SetTransform(rot);
	gfx->GetRenderTarget()->DrawBitmap(
		bmp,
		D2D1::RectF(topLeftX, topLeftY, topLeftX + w, topLeftY + h),
		kOPAQUE,
		D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		D2D1::RectF(kDEFAULT, kDEFAULT, bmp->GetSize().width, bmp->GetSize().height)
	);

}



/**
 * \brief Used to apply
 * \param pv A pointer to the raw image source to be transformed
 * \param width The width of the image
 * \param height The height of the image
 */
void BitmapImage::GreenScreenFilter(BYTE* pv, int width, int height)
{
	for (int i = kDEFAULT; i < width * height * kSIZE_OF_INT; i += kSIZE_OF_INT)
	{
		if (pv[i + kRED_INT_INDEX] < kRED_THRESHOLD
			&& pv[i + kGREEN_INT_INDEX] > kGREEN_THRESHOLD
			&& pv[i + kBLUE_INT_INDEX] < kBLUE_THRESHOLD)
		{
			pv[i + kGREEN_INT_INDEX] = kBLOCK_IS_EMPTY;
			pv[i + kALPHA_INT_INDEX] = kBLOCK_IS_EMPTY;
		}
	}
}



/**
 * \brief This function is used to produce a bitmap that has the chroma key filter applied
 * \return Indicates the success of the chroma key application
 */
bool BitmapImage::DoChroma()
{
	bool ret = true;
	HRESULT hr;
	UINT width = kDEFAULT;
	UINT height = kDEFAULT;
	wicFrame->GetSize(&width, &height);
	UINT uiWidth = kINEXPLICABLE_DEFAULT_RECT_SIZE;
	UINT uiHeight = kINEXPLICABLE_DEFAULT_RECT_SIZE;
	WICRect rcLock = { kDEFAULT, kDEFAULT, (int)uiWidth, (int)uiHeight };
	D2D1_SIZE_U size = D2D1::SizeU(rcLock.Width, rcLock.Height);
	// Create the bitmap from the image frame.

	hr = wicFactory->CreateFormatConverter(&wicConverter);

	//Step 5: Configure the Converter
	hr = wicConverter->Initialize(
		wicFrame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		nullptr,
		kDEFAULT,
		WICBitmapPaletteTypeCustom
	);

	hr = wicFactory->CreateBitmapFromSource(
		wicConverter,
		WICBitmapCacheOnDemand,
		&pIBitmap);


	if (SUCCEEDED(hr))
	{
		// Obtain a bitmap lock for exclusive write.
		// The lock is for a 10x10 rectangle starting at the top left of the
		// bitmap.
		hr = pIBitmap->Lock(&rcLock, WICBitmapLockWrite, &pILock);

		if (SUCCEEDED(hr))
		{
			UINT cbBufferSize = kDEFAULT;
			BYTE* pv = nullptr;

			// Retrieve a pointer to the pixel data.
			if (SUCCEEDED(hr))
			{
				hr = pILock->GetDataPointer(&cbBufferSize, &pv);
			}

			pIBitmap->GetSize(&width, &height);
			GreenScreenFilter(pv, width, height);

			// Release the bitmap lock.
			if (pILock)
			{
				pILock->Release();
				pILock = NULL;
			}

		}
	}
	//IWICFormatConverter* wicConverter = nullptr;
	hr = wicFactory->CreateFormatConverter(&wicConverter);

	//Step 5: Configure the Converter
	hr = wicConverter->Initialize(
		pIBitmap,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		nullptr,
		kDEFAULT,
		WICBitmapPaletteTypeCustom
	);
	return ret;
}

/**
 * \brief This method is used to retrieve the graphics object driving the bitmap image
 * \return The graphics object
 */
Graphics* BitmapImage::GetGraphics()
{
	return this->gfx;
}
