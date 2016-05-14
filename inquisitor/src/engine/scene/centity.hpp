#ifndef CENTITY_HPP
#define CENTITY_HPP

#include <string>

typedef std::uint32_t EntityID;

class CEntity final
{
	public:
		CEntity();
		~CEntity();

	private:
		const EntityID m_uuid = s_lastID++;

		static EntityID s_lastID;
};

#endif // COBJECT_HPP
