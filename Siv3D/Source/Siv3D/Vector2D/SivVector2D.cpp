﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Vector2D.hpp>

namespace s3d
{
	template Float2;
	template Vec2;

	void Formatter(FormatData& formatData, const Float2& value)
	{
		Formatter(formatData, Vec2(value));
	}

	void Formatter(FormatData& formatData, const Vec2& value)
	{
		formatData.string.push_back(L'(');
		formatData.string.append(ToString(value.x, formatData.decimalPlace.value));
		formatData.string.push_back(L',');
		formatData.string.append(ToString(value.y, formatData.decimalPlace.value));
		formatData.string.push_back(L')');
	}
}
