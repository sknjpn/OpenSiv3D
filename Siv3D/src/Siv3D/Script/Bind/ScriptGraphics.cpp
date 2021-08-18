﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Script.hpp>
# include <Siv3D/Graphics.hpp>

namespace s3d
{
	using namespace AngelScript;

	void RegisterGraphics(asIScriptEngine* engine)
	{
		int32 r = 0;

		r = engine->SetDefaultNamespace("Graphics"); assert(r >= 0);
		{
			engine->RegisterGlobalFunction("void SetVSyncEnabled(bool)", asFUNCTION(Graphics::SetVSyncEnabled), asCALL_CDECL); assert(r >= 0);
			engine->RegisterGlobalFunction("bool IsVSyncEnabled()", asFUNCTION(Graphics::IsVSyncEnabled), asCALL_CDECL); assert(r >= 0);
		}
		r = engine->SetDefaultNamespace(""); assert(r >= 0);
	}
}
