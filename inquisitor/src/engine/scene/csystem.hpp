#ifndef CSYSTEM_HPP
#define CSYSTEM_HPP


class CSystem
{
	public:
		virtual ~CSystem();
		virtual void Update( const double dt ) = 0;
};

#endif // CSYSTEM_HPP
