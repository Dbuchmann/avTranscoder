#include "UnknownProperties.hpp"

namespace avtranscoder
{

UnknownProperties::UnknownProperties( const FormatContext& formatContext, const size_t index )
	: _formatContext( &formatContext.getAVFormatContext() )
	, _streamId( index )
{
	if( _formatContext )
		detail::fillMetadataDictionnary( _formatContext->streams[index]->metadata, _metadatas );
}

PropertiesMap UnknownProperties::getPropertiesAsMap() const
{
	PropertiesMap dataMap;

	detail::add( dataMap, "streamId", _streamId );

	for( size_t metadataIndex = 0; metadataIndex < _metadatas.size(); ++metadataIndex )
	{
		detail::add( dataMap, _metadatas.at( metadataIndex ).first, _metadatas.at( metadataIndex ).second );
	}

	return dataMap;
}

}
