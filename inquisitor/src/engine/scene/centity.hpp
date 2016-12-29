#ifndef CENTITY_HPP
#define CENTITY_HPP

#include <string>

using EntityID = std::uint32_t;

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
