﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "CShader_GLES3.hpp"
# include <Siv3D/TextReader.hpp>
# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/ConstantBuffer/GLES3/ConstantBufferDetail_GLES3.hpp>

namespace s3d
{
	CShader_GLES3::CShader_GLES3()
	{

	}

	CShader_GLES3::~CShader_GLES3()
	{
		LOG_SCOPED_TRACE(U"CShader_GLES3::~CShader_GLES3()");

		if (m_pipeline)
		{
			::glDeleteProgramPipelines(1, &m_pipeline);
			m_pipeline = 0;
		}

		m_pixelShaders.destroy();
		m_vertexShaders.destroy();
	}

	void CShader_GLES3::init()
	{
		LOG_SCOPED_TRACE(U"CShader_GLES3::init()");

		// null VS を管理に登録
		{
			// null VS を作成
			auto nullVertexShader = std::make_unique<GLES3VertexShader>(GLES3VertexShader::Null{});

			if (!nullVertexShader->isInitialized()) // もし作成に失敗していたら
			{
				throw EngineError(U"Null VertexShader initialization failed");
			}

			// 管理に登録
			m_vertexShaders.setNullData(std::move(nullVertexShader));
		}

		// null PS を管理に登録
		{
			// null PS を作成
			auto nullPixelShader = std::make_unique<GLES3PixelShader>(GLES3PixelShader::Null{});

			if (!nullPixelShader->isInitialized()) // もし作成に失敗していたら
			{
				throw EngineError(U"Null PixelShader initialization failed");
			}

			// 管理に登録
			m_pixelShaders.setNullData(std::move(nullPixelShader));
		}

		::glGenProgramPipelines(1, &m_pipeline);

		if (!m_pipeline)
		{
			throw EngineError(U"glGenProgramPipelines() failed");
		}
	}

	VertexShader::IDType CShader_GLES3::createVSFromFile(const FilePathView path, const StringView entryPoint, const Array<ConstantBufferBinding>& bindings)
	{
		TextReader reader(path);

		if (not reader)
		{
			return VertexShader::IDType::NullAsset();
		}

		return createVSFromSource(reader.readAll(), entryPoint, bindings);
	}

	VertexShader::IDType CShader_GLES3::createVSFromSource(const StringView source, const StringView, const Array<ConstantBufferBinding>& bindings)
	{
		// VS を作成
		auto vertexShader = std::make_unique<GLES3VertexShader>(source, bindings);

		if (!vertexShader->isInitialized()) // もし作成に失敗していたら
		{
			return VertexShader::IDType::NullAsset();
		}

		// VS を管理に登録
		return m_vertexShaders.add(std::move(vertexShader));
	}

	PixelShader::IDType CShader_GLES3::createPSFromFile(const FilePathView path, const StringView entryPoint, const Array<ConstantBufferBinding>& bindings)
	{
		TextReader reader(path);

		if (not reader)
		{
			return PixelShader::IDType::NullAsset();
		}

		return createPSFromSource(reader.readAll(), entryPoint, bindings);
	}

	PixelShader::IDType CShader_GLES3::createPSFromSource(const StringView source, const StringView, const Array<ConstantBufferBinding>& bindings)
	{
		// PS を作成
		auto pixelShader = std::make_unique<GLES3PixelShader>(source, bindings);

		if (!pixelShader->isInitialized()) // もし作成に失敗していたら
		{
			return PixelShader::IDType::NullAsset();
		}

		// PS を管理に登録
		return m_pixelShaders.add(std::move(pixelShader));
	}

	void CShader_GLES3::releaseVS(const VertexShader::IDType handleID)
	{
		// 指定した VS を管理から除外
		m_vertexShaders.erase(handleID);
	}

	void CShader_GLES3::releasePS(const PixelShader::IDType handleID)
	{
		// 指定した PS を管理から除外
		m_pixelShaders.erase(handleID);
	}

	void CShader_GLES3::setVS(const VertexShader::IDType handleID)
	{
		const GLuint vsProgram = m_vertexShaders[handleID]->getProgram();
		::glUseProgramStages(m_pipeline, GL_VERTEX_SHADER_BIT, vsProgram);
	}

	void CShader_GLES3::setPS(const PixelShader::IDType handleID)
	{
		const auto& pixelShader = m_pixelShaders[handleID];

		const GLuint psProgram = pixelShader->getProgram();
		::glUseProgramStages(m_pipeline, GL_FRAGMENT_SHADER_BIT, psProgram);

		pixelShader->setPSSamplerUniform();
	}

	const Blob& CShader_GLES3::getBinaryVS(const VertexShader::IDType handleID)
	{
		return m_vertexShaders[handleID]->getBinary();
	}

	const Blob& CShader_GLES3::getBinaryPS(const PixelShader::IDType handleID)
	{
		return m_pixelShaders[handleID]->getBinary();
	}

	void CShader_GLES3::setConstantBufferVS(const uint32 slot, const ConstantBufferBase& cb)
	{
		const uint32 vsUniformBlockBinding = Shader::Internal::MakeUniformBlockBinding(ShaderStage::Vertex, slot);
		::glBindBufferBase(GL_UNIFORM_BUFFER, vsUniformBlockBinding, dynamic_cast<const ConstantBufferDetail_GLES3*>(cb._detail())->getHandle());
	}

	void CShader_GLES3::setConstantBufferPS(const uint32 slot, const ConstantBufferBase& cb)
	{
		const uint32 psUniformBlockBinding = Shader::Internal::MakeUniformBlockBinding(ShaderStage::Pixel, slot);
		::glBindBufferBase(GL_UNIFORM_BUFFER, psUniformBlockBinding, dynamic_cast<const ConstantBufferDetail_GLES3*>(cb._detail())->getHandle());
	}

	void CShader_GLES3::usePipeline()
	{
		::glUseProgram(0);
		::glBindProgramPipeline(m_pipeline);
	}
}
