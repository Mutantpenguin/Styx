#ifndef CTEXCOORDMOD_HPP
#define CTEXCOORDMOD_HPP

#include <array>

#include <glm/glm.hpp>

class CTexCoordMod
{
public:
	virtual const glm::mat3 &Update( const float );

protected:
	glm::mat3 m_mat;
};

class CTexCoordModRotate final : public CTexCoordMod
{
public:
    CTexCoordModRotate( float deg );

    const glm::mat3 &Update( const float delta ) override;

private:
	const float m_rad;

	float m_radCurrent { 0.0f };
};

class CTexCoordModScale final : public CTexCoordMod
{
public:
    CTexCoordModScale( float uscale, float vscale );
};

class CTexCoordModScroll final : public CTexCoordMod
{
public:
    CTexCoordModScroll( float uspeed, float vspeed );

    const glm::mat3 &Update( const float delta ) override;

private:
	const std::array< float, 2 > m_speed;

	std::array< float, 2 > m_currentscroll { { 0.0f, 0.0f } };
};

class CTexCoordModMove final : public CTexCoordMod
{
public:
    CTexCoordModMove( float umove, float vmove );
};

#endif // CTEXCOORDMOD_HPP
