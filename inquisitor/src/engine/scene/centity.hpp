#ifndef CENTITY_HPP
#define CENTITY_HPP

#include <string>

typedef std::string EntityID;

class CEntity final
{
	public:
		CEntity();
		~CEntity();

	private:
		EntityID m_uuid;
};

#endif // COBJECT_HPP
