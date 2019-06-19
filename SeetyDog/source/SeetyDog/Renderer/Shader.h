#pragma once

#include <string>

namespace SeetyDog {

	class Shader {

		Shader(const std::string& vertexSource, const std::string& fragmentSource);
		~Shader();

		void Bind() const;
		void Unbind() const;

	private:
		uint32_t m_RendererID;


	};
}