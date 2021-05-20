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

# pragma once
# include <memory>
# include "Common.hpp"
# include "Optional.hpp"
# include "Unspecified.hpp"
# include "PredefinedYesNo.hpp"

namespace s3d
{
	/// @brief マイク
	class Microphone
	{
	public:

		static constexpr size_t DefaultBuffreLength = (48'000 * 5);

		enum class Permission
		{
			Allowed,

			Denied,
		};

		SIV3D_NODISCARD_CXX20
		Microphone();

		SIV3D_NODISCARD_CXX20
		explicit Microphone(const Optional<size_t> deviceIndex, Optional<uint32> sampleRate = unspecified, size_t bufferLength = DefaultBuffreLength, Loop loop = Loop::Yes, StartImmediately startImmediately = StartImmediately::No);

		~Microphone();

		[[nodiscard]]
		Optional<Permission> getPermission() const;

		bool open(const Optional<size_t> deviceIndex, Optional<uint32> sampleRate = unspecified, size_t bufferLength = DefaultBuffreLength, Loop loop = Loop::Yes, StartImmediately startImmediately = StartImmediately::No);

		void close();

		[[nodiscard]]
		bool isOpen() const;

		[[nodiscard]]
		explicit operator bool() const;

		bool start();

		[[nodiscard]]
		bool isActive() const;

		[[nodiscard]]
		size_t microphoneIndex() const;

		[[nodiscard]]
		uint32 getSampleRate() const;

		[[nodiscard]]
		size_t getBufferLength() const;

		[[nodiscard]]
		bool isLoop() const;

		[[nodiscard]]
		const Wave& getBuffer() const;

		[[nodiscard]]
		size_t posSample() const;

		[[nodiscard]]
		double mean(const Duration& duration = SecondsF{ 0.02 }) const;

		[[nodiscard]]
		double rootMeanSquare(const Duration& duration = SecondsF{ 0.02 }) const;

		[[nodiscard]]
		double peak(const Duration& duration = SecondsF{ 0.02 }) const;

		//void fft(FFTResult& result, FFTSampleLength sampleLength = FFTSampleLength::Default) const;

	private:

		class MicrophoneDetail;

		std::shared_ptr<MicrophoneDetail> pImpl;
	};
}
