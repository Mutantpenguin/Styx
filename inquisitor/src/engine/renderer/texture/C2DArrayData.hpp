#ifndef C2DARRAYDATA_HPP
#define C2DARRAYDATA_HPP

#include <cstdint>
#include <vector>
#include <memory>

#include "../../helper/image/CImage.hpp"

class C2DArrayData final
{
public:
	bool AddLayer( const std::shared_ptr< const CImage > &image );

	const std::vector< std::shared_ptr< const CImage > > &getLayers( void ) const;

private:
	std::vector< std::shared_ptr< const CImage > > m_layers;
};

#endif // C2DARRAYDATA_HPP
