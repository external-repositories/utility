private:
template< typename DerivedStream >
basic_RecordOrientedStream( std::unique_ptr< DerivedStream >&& core, const long lineNumber ) :
  Stream( std::make_unique< Streambuf >( *(core->rdbuf()),
					 this->buffer,
					 this->lineNumber ).release() ),
  core( std::move( core ) ), lineNumber( lineNumber ){ }

public:
template< typename DerivedStream >
basic_RecordOrientedStream( DerivedStream&& core, const long lineNumber = 1 ) :
  basic_RecordOrientedStream( std::make_unique
			      < DerivedStream >( std::move( core ) ), lineNumber ){}

basic_RecordOrientedStream( std::string&& str ) :
    basic_RecordOrientedStream( std::istringstream( str ) ) { }

basic_RecordOrientedStream( const basic_RecordOrientedStream& ) = delete;

basic_RecordOrientedStream( basic_RecordOrientedStream&& other ){
  this->rdbuf() = other.rdbuf();
  this->buffer = std::move(other.buffer);
  this->lineNumber = other.lineNumber;
  other.rdbuf( nullptr );
}