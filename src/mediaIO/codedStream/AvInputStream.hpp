#ifndef _MEDIA_ENGINE_IO_CODED_STREAM_AV_INPUT_STREAM_HPP_
#define _MEDIA_ENGINE_IO_CODED_STREAM_AV_INPUT_STREAM_HPP_

#include "IInputStream.hpp"

struct AVStream;

namespace mediaengine
{
namespace mediaio
{

class InputFile;

class MediaEngineExport AvInputStream : public IInputStream
{
public:
	AvInputStream( InputFile& inputFile, const size_t streamIndex );
	AvInputStream( const AvInputStream& inputStream );

	~AvInputStream( );

	size_t getStreamIndex() const { return _streamIndex; }

	bool readNextPacket( mediacore::CodedData& data );

	// Stream properties
	VideoCodec& getVideoCodec();
	AudioCodec& getAudioCodec();
	DataCodec& getDataCodec();

	AVMediaType getStreamType() const;

	double getDuration() const;
	double getPacketDuration() const;

	void addPacket( AVPacket& packet );

	void setBufferred( const bool bufferized ){ _bufferized = bufferized; };
	bool getBufferred() const { return _bufferized; };

	void clearBuffering();

private:
	AVStream* getAVStream() const;

private:
	InputFile*       _inputFile;
	std::vector<mediacore::CodedData> _streamCache;

	ICodec* _codec;  ///< Has ownership

	int              _packetDuration;
	size_t           _streamIndex;
	bool             _bufferized;
};

}
}

#endif