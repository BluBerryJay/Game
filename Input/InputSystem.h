#pragma once
#include <SDL2-2.28.0/include/SDL.h>
#include "../Source/Engine/Core/Core.h"
#include <vector>
#include <array>
using namespace std;
namespace kiko
{
	class InputSystem
	{
	public:
		InputSystem() = default;
		~InputSystem() = default;
		const Vector2& GetMousePosition() const { return m_mousePosition; }

		bool GetMouseButtonDown(uint32_t button) { return m_mouseButtonState[button]; }
		bool GetMousePreviousButtonDown(uint32_t button) { return m_prevMouseButtonState[button]; }

		bool Initialize();
		void Shutdown();
		void Update();
		bool GetKeyDown(uint32_t key) const { return m_keyboardState[key]; }
		bool GetPreviousKeyDown(uint32_t key) const { return m_prevKeyboardState[key]; }

	private:
		Vector2 m_mousePosition;
		
		std::array<uint8_t, 3> m_mouseButtonState;
		std::array<uint8_t, 3> m_prevMouseButtonState;
		
		std::vector<uint8_t> m_keyboardState;
		std::vector<uint8_t> m_prevKeyboardState;


	};
	extern InputSystem g_inSys;
}