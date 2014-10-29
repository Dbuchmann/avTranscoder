#include "GeneratorVideo.hpp"

#include <mediaTransform/VideoTransform.hpp>

namespace mediaengine
{
namespace mediaio
{

GeneratorVideo::GeneratorVideo( )
	: IInputEssence( )
	, _codec( NULL )
	, _inputFrame( NULL )
	, _videoFrameDesc()
	, _numberOfView( 1 )
{
}

void GeneratorVideo::setVideoCodec( const VideoCodec& codec )
{
	_codec = &codec;
	_videoFrameDesc = _codec->getVideoFrameDesc();
}

const VideoCodec& GeneratorVideo::getVideoCodec()
{
	return *_codec;
}

void GeneratorVideo::setFrame( mediacore::Frame& inputFrame )
{
	_inputFrame = &inputFrame;
}

bool GeneratorVideo::readNextFrame( mediacore::Frame& frameBuffer )
{
	if( ! _inputFrame )
	{
		// @todo support PAL (0 to 255) and NTFS (16 to 235)
		int fillChar = 0;

		if( frameBuffer.getSize() != _videoFrameDesc.getDataSize() )
			frameBuffer.getBuffer().resize( _videoFrameDesc.getDataSize() );

		mediacore::VideoFrameDesc desc( _codec->getVideoFrameDesc() );
		mediacore::Pixel rgbPixel;
		rgbPixel.setColorComponents( mediacore::eComponentRgb );
		rgbPixel.setPlanar( false );
		desc.setPixel( rgbPixel );

		mediacore::VideoFrame intermediateBuffer( desc );
		intermediateBuffer.getBuffer().resize( _videoFrameDesc.getDataSize() );
		memset( intermediateBuffer.getPtr(), fillChar, _videoFrameDesc.getDataSize() );

		mediatransform::VideoTransform videoEssenceTransform;
		videoEssenceTransform.convert( intermediateBuffer, frameBuffer );

		return true;
	}
	
	if( frameBuffer.getSize() != _inputFrame->getSize() )
		frameBuffer.getBuffer().resize( _inputFrame->getSize() );
	std::memcpy( frameBuffer.getPtr(), _inputFrame->getPtr(), _inputFrame->getSize() );
	return true;
}

bool GeneratorVideo::readNextFrame( mediacore::Frame& frameBuffer, const size_t subStreamIndex )
{
	return false;
}

}
}