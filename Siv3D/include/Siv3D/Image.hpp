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
# include "Common.hpp"
# include "Array.hpp"
# include "Grid.hpp"
# include "NamedParameter.hpp"
# include "PredefinedNamedParameter.hpp"
# include "ImageFormat.hpp"
# include "ImageAddressMode.hpp"
# include "PointVector.hpp"
# include "ColorHSV.hpp"
# include "IReader.hpp"
# include "PNGFilter.hpp"
# include "BorderType.hpp"
# include "AdaptiveThresholdMethod.hpp"
# include "FloodFillConnectivity.hpp"
# include "InterpolationAlgorithm.hpp"
# include "PredefinedYesNo.hpp"

namespace s3d
{
	struct Emoji;
	struct Icon;
	struct ImageROI;
	struct ImageConstROI;

	class Image
	{
	public:

		/// @brief 作成可能な最大の画像の幅
		static constexpr int32 MaxWidth		= 16384;

		/// @brief 作成可能な最大の画像の高さ
		static constexpr int32 MaxHeight	= 16384;

		using base_type					= Array<Color>;
		using iterator					= base_type::iterator;
		using const_iterator			= base_type::const_iterator;
		using reverse_iterator			= base_type::reverse_iterator;
		using const_reverse_iterator	= base_type::const_reverse_iterator;

		SIV3D_NODISCARD_CXX20
		Image() = default;

		SIV3D_NODISCARD_CXX20
		Image(const Image&) = default;

		SIV3D_NODISCARD_CXX20
		Image(Image&& image) noexcept;

		SIV3D_NODISCARD_CXX20
		explicit Image(size_t size);

		SIV3D_NODISCARD_CXX20
		explicit Image(size_t size, Color color);

		template <class Fty, std::enable_if_t<std::disjunction_v<std::is_invocable_r<Color, Fty>, std::is_invocable_r<Color, Fty, Point>, std::is_invocable_r<Color, Fty, int32, int32>>>* = nullptr>
		SIV3D_NODISCARD_CXX20
		Image(size_t size, Arg::generator_<Fty> generator);

		template <class Fty, std::enable_if_t<std::disjunction_v<std::is_invocable_r<Color, Fty, Vec2>, std::is_invocable_r<Color, Fty, double, double>>>* = nullptr>
		SIV3D_NODISCARD_CXX20
		Image(size_t size, Arg::generator0_1_<Fty> generator);

		SIV3D_NODISCARD_CXX20
		Image(size_t width, size_t height);

		SIV3D_NODISCARD_CXX20
		Image(size_t width, size_t height, Color color);

		template <class Fty, std::enable_if_t<std::disjunction_v<std::is_invocable_r<Color, Fty>, std::is_invocable_r<Color, Fty, Point>, std::is_invocable_r<Color, Fty, int32, int32>>>* = nullptr>
		SIV3D_NODISCARD_CXX20
		Image(size_t width, size_t height, Arg::generator_<Fty> generator);

		template <class Fty, std::enable_if_t<std::disjunction_v<std::is_invocable_r<Color, Fty, Vec2>, std::is_invocable_r<Color, Fty, double, double>>>* = nullptr>
		SIV3D_NODISCARD_CXX20
		Image(size_t width, size_t height, Arg::generator0_1_<Fty> generator);

		SIV3D_NODISCARD_CXX20
		explicit Image(Size size);

		SIV3D_NODISCARD_CXX20
		Image(Size size, Color color);

		template <class Fty, std::enable_if_t<std::disjunction_v<std::is_invocable_r<Color, Fty>, std::is_invocable_r<Color, Fty, Point>, std::is_invocable_r<Color, Fty, int32, int32>>>* = nullptr>
		SIV3D_NODISCARD_CXX20
		Image(Size size, Arg::generator_<Fty> generator);

		template <class Fty, std::enable_if_t<std::disjunction_v<std::is_invocable_r<Color, Fty, Vec2>, std::is_invocable_r<Color, Fty, double, double>>>* = nullptr>
		SIV3D_NODISCARD_CXX20
		Image(Size size, Arg::generator0_1_<Fty> generator);

		SIV3D_NODISCARD_CXX20
		explicit Image(FilePathView path, ImageFormat format = ImageFormat::Unspecified);

		SIV3D_NODISCARD_CXX20
		explicit Image(IReader&& reader, ImageFormat format = ImageFormat::Unspecified);

		SIV3D_NODISCARD_CXX20
		Image(FilePathView rgb, FilePathView alpha);

		SIV3D_NODISCARD_CXX20
		Image(Color rgb, FilePathView alpha);

		SIV3D_NODISCARD_CXX20
		explicit Image(const Emoji& emoji);

		SIV3D_NODISCARD_CXX20
		explicit Image(const Icon& icon, int32 size);

		SIV3D_NODISCARD_CXX20
		explicit Image(const Grid<Color>& grid);

		SIV3D_NODISCARD_CXX20
		explicit Image(const Grid<ColorF>& grid);

		template <class Type, class Fty, std::enable_if_t<std::is_invocable_r_v<Color, Fty, Type>>* = nullptr>
		SIV3D_NODISCARD_CXX20
		explicit Image(const Grid<Type>& grid, Fty converter);

		Image& operator =(const Image&) = default;

		Image& operator =(Image && image) noexcept;

		/// <summary>
		/// 画像の幅（ピクセル）
		/// </summary>
		[[nodiscard]]
		int32 width() const noexcept;

		/// <summary>
		/// 画像の高さ（ピクセル）
		/// </summary>
		[[nodiscard]]
		int32 height() const noexcept;

		/// <summary>
		/// 画像の幅と高さ（ピクセル）
		/// </summary>
		[[nodiscard]]
		Size size() const noexcept;

		/// <summary>
		/// 画像の各行のデータサイズ
		/// </summary>
		[[nodiscard]]
		uint32 stride() const noexcept;

		/// <summary>
		/// 画像のピクセル数
		/// </summary>
		[[nodiscard]]
		uint32 num_pixels() const noexcept;

		/// <summary>
		/// 画像のデータサイズ
		/// </summary>
		[[nodiscard]]
		uint32 size_bytes() const noexcept;

		[[nodiscard]]
		bool isEmpty() const noexcept;

		[[nodiscard]]
		explicit operator bool() const noexcept;

		/// <summary>
		/// 画像の不要なメモリ消費を削除します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void shrink_to_fit();

		/// <summary>
		/// 画像を消去し、空の画像にします。
		/// </summary>
		/// <remarks>
		/// メモリを解放したい場合は shrink_to_fit() を呼びます。
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void clear() noexcept;

		void release();

		/// <summary>
		/// 画像を別の画像と交換します。
		/// </summary>
		/// <param name="image">
		/// 交換する画像
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void swap(Image& image) noexcept;

		/// <summary>
		/// 画像をコピーした新しい画像を返します。
		/// </summary>
		/// <returns>
		/// コピーした新しい画像
		/// </returns>
		[[nodiscard]]
		Image cloned() const;

		/// <summary>
		/// 指定した行の先頭ポインタを返します。
		/// </summary>
		/// <param name="y">
		/// 位置(行)
		/// </param>
		/// <returns>
		/// image[y][x] で指定したピクセルにアクセスします。
		/// </returns>
		/// <returns>
		/// 指定した行の先頭ポインタ
		/// </returns>
		[[nodiscard]]
		Color* operator[](size_t y);

		[[nodiscard]]
		Color& operator[](Point pos);

		/// <summary>
		/// 指定した行の先頭ポインタを返します。
		/// </summary>
		/// <param name="y">
		/// 位置(行)
		/// </param>
		/// <returns>
		/// image[y][x] で指定したピクセルにアクセスします。
		/// </returns>
		/// <returns>
		/// 指定した行の先頭ポインタ
		/// </returns>
		[[nodiscard]]
		const Color* operator[](size_t y) const;

		[[nodiscard]]
		const Color& operator[](Point pos) const;

		/// <summary>
		/// 画像データの先頭のポインタを返します。
		/// </summary>
		/// <returns>
		/// 画像データの先頭へのポインタ
		/// </returns>
		[[nodiscard]]
		Color* data();

		/// <summary>
		/// 画像データの先頭のポインタを返します。
		/// </summary>
		/// <returns>
		/// 画像データの先頭へのポインタ
		/// </returns>
		[[nodiscard]]
		const Color* data() const;

		/// <summary>
		/// 画像データの先頭のポインタを返します。
		/// </summary>
		/// <returns>
		/// 画像データの先頭へのポインタ
		/// </returns>
		[[nodiscard]]
		uint8* dataAsUint8();

		/// <summary>
		/// 画像データの先頭のポインタを返します。
		/// </summary>
		/// <returns>
		/// 画像データの先頭へのポインタ
		/// </returns>
		[[nodiscard]]
		const uint8* dataAsUint8() const;

		[[nodiscard]]
		Array<Color> asArray() const&;

		[[nodiscard]]
		Array<Color> asArray()&&;

		[[nodiscard]]
		iterator begin() noexcept;

		[[nodiscard]]
		iterator end() noexcept;

		[[nodiscard]]
		const_iterator begin() const noexcept;

		[[nodiscard]]
		const_iterator end() const noexcept;

		[[nodiscard]]
		const_iterator cbegin() const noexcept;

		[[nodiscard]]
		const_iterator cend() const noexcept;

		[[nodiscard]]
		reverse_iterator rbegin() noexcept;

		[[nodiscard]]
		reverse_iterator rend() noexcept;

		[[nodiscard]]
		const_reverse_iterator rbegin() const noexcept;

		[[nodiscard]]
		const_reverse_iterator rend() const noexcept;

		[[nodiscard]]
		const_reverse_iterator crbegin() const noexcept;

		[[nodiscard]]
		const_reverse_iterator crend() const noexcept;

		/// <summary>
		/// 画像を指定した色で塗りつぶします。
		/// </summary>
		/// <param name="color">
		/// 塗りつぶしの色
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void fill(Color color) noexcept;

		void resize(size_t width, size_t height);

		void resize(Size size);

		void resize(size_t width, size_t height, Color fillColor);

		void resize(Size size, Color fillColor);

		void resizeRows(size_t rows, Color fillColor);

		[[nodiscard]]
		Color getPixel(int32 x, int32 y, ImageAddressMode addressMode) const;

		[[nodiscard]]
		Color getPixel(Point pos, ImageAddressMode addressMode) const;

		[[nodiscard]]
		ColorF samplePixel(double x, double y, ImageAddressMode addressMode) const;

		[[nodiscard]]
		ColorF samplePixel(Vec2 pos, ImageAddressMode addressMode) const;

		[[nodiscard]]
		Image clipped(const Rect& rect) const;

		[[nodiscard]]
		Image clipped(int32 x, int32 y, int32 w, int32 h) const;

		[[nodiscard]]
		Image clipped(const Point& pos, int32 w, int32 h) const;

		[[nodiscard]]
		Image clipped(int32 x, int32 y, const Size& size) const;

		[[nodiscard]]
		Image clipped(const Point& pos, const Size& size) const;

		[[nodiscard]]
		Image squareClipped() const;

		template <class Fty>
		Image& forEach(Fty f);

		template <class Fty>
		const Image& forEach(Fty f) const;

		Image& RGBAtoBGRA();

		bool applyAlphaFromRChannel(FilePathView alpha);

		bool save(FilePathView path, ImageFormat format = ImageFormat::Unspecified) const;

		//bool saveWithDialog() const;

		bool savePNG(FilePathView path, PNGFilter filter = PNGFilter::Default) const;

		//bool saveJPEG(FilePathView path, int32 quality = 90) const;

		//bool savePPM(FilePathView path, PPMType format = PPMType::AsciiRGB) const;

		//bool saveWebP(FilePathView path, bool lossless = false, double quality = 90.0, WebPMethod method = WebPMethod::Default) const;

		Image& negate();

		[[nodiscard]]
		Image negated() const;

		Image& grayscale();

		[[nodiscard]]
		Image grayscaled() const;

		Image& sepia(int32 level = 25);

		[[nodiscard]]
		Image sepiaed(int32 level = 25) const;

		Image& posterize(int32 level);

		[[nodiscard]]
		Image posterized(int32 level) const;

		Image& brighten(int32 level);

		[[nodiscard]]
		Image brightened(int32 level) const;

		Image& mirror();

		[[nodiscard]]
		Image mirrored() const;

		Image& flip();

		[[nodiscard]]
		Image flipped() const;

		Image& rotate90();

		[[nodiscard]]
		Image rotated90() const;

		Image& rotate180();

		[[nodiscard]]
		Image rotated180() const;

		Image& rotate270();

		[[nodiscard]]
		Image rotated270() const;

		Image& gammaCorrect(double gamma);

		[[nodiscard]]
		Image gammaCorrected(double gamma) const;

		Image& threshold(uint8 threshold, InvertColor invertColor = InvertColor::No);

		[[nodiscard]]
		Image thresholded(uint8 threshold, InvertColor invertColor = InvertColor::No) const;

		Image& threshold_Otsu(InvertColor invertColor = InvertColor::No);

		[[nodiscard]]
		Image thresholded_Otsu(InvertColor invertColor = InvertColor::No) const;

		Image& adaptiveThreshold(AdaptiveThresholdMethod method, int32 blockSize, double c, InvertColor invertColor = InvertColor::No);

		[[nodiscard]]
		Image adaptiveThresholded(AdaptiveThresholdMethod method, int32 blockSize, double c, InvertColor invertColor = InvertColor::No) const;

		Image& mosaic(int32 size);

		Image& mosaic(int32 horizontal, int32 vertical);

		[[nodiscard]]
		Image mosaiced(int32 size) const;

		[[nodiscard]]
		Image mosaiced(int32 horizontal, int32 vertical) const;

		Image& spread(int32 size);

		Image& spread(int32 horizontal, int32 vertical);

		[[nodiscard]]
		Image spreaded(int32 size) const;

		[[nodiscard]]
		Image spreaded(int32 horizontal, int32 vertical) const;

		Image& blur(int32 size);

		Image& blur(int32 horizontal, int32 vertical);

		[[nodiscard]]
		Image blurred(int32 size) const;

		[[nodiscard]]
		Image blurred(int32 horizontal, int32 vertical) const;

		Image& medianBlur(int32 apertureSize);

		[[nodiscard]]
		Image medianBlurred(int32 apertureSize) const;

		Image& gaussianBlur(int32 size, BorderType borderType = BorderType::Default);

		Image& gaussianBlur(int32 horizontal, int32 vertical, BorderType borderType = BorderType::Default);

		[[nodiscard]]
		Image gaussianBlurred(int32 size, BorderType borderType = BorderType::Default) const;

		[[nodiscard]]
		Image gaussianBlurred(int32 horizontal, int32 vertical, BorderType borderType = BorderType::Default) const;

		Image& dilate(int32 iterations = 1);

		[[nodiscard]]
		Image dilated(int32 iterations = 1) const;

		Image& erode(int32 iterations = 1);

		[[nodiscard]]
		Image eroded(int32 iterations = 1) const;

		//Image& floodFill(const Point& pos, const Color& color, FloodFillConnectivity connectivity = FloodFillConnectivity::Value4, int32 lowerDifference = 0, int32 upperDifference = 0);

		//[[nodiscard]]
		//Image floodFilled(const Point& pos, const Color& color, FloodFillConnectivity connectivity = FloodFillConnectivity::Value4, int32 lowerDifference = 0, int32 upperDifference = 0) const;

		//Image& scale(int32 width, int32 height, Interpolation interpolation = Interpolation::Unspecified);

		//[[nodiscard]]
		//Image scaled(int32 width, int32 height, Interpolation interpolation = Interpolation::Unspecified) const;

		//Image& scale(const Size& size, Interpolation interpolation = Interpolation::Unspecified);

		//[[nodiscard]]
		//Image scaled(const Size& size, Interpolation interpolation = Interpolation::Unspecified) const;

		//Image& scale(double scaling, Interpolation interpolation = Interpolation::Unspecified);

		//[[nodiscard]]
		//Image scaled(double scaling, Interpolation interpolation = Interpolation::Unspecified) const;

		//Image& fit(int32 width, int32 height, bool scaleUp = true, Interpolation interpolation = Interpolation::Unspecified);

		//[[nodiscard]]
		//Image fitted(int32 width, int32 height, bool scaleUp = true, Interpolation interpolation = Interpolation::Unspecified) const;

		//Image& fit(const Size& size, bool scaleUp = true, Interpolation interpolation = Interpolation::Unspecified);

		//[[nodiscard]]
		//Image fitted(const Size& size, bool scaleUp = true, Interpolation interpolation = Interpolation::Unspecified) const;

		Image& border(int32 thickness, const Color& color = Palette::White);

		[[nodiscard]]
		Image bordered(int32 thickness, const Color& color = Palette::White) const;

		Image& border(int32 top, int32 right, int32 bottom, int32 left, const Color& color = Palette::White);

		[[nodiscard]]
		Image bordered(int32 top, int32 right, int32 bottom, int32 left, const Color& color = Palette::White) const;

		void paint(Image& dst, int32 x, int32 y, const Color& color = Palette::White) const;

		void paint(Image& dst, const Point& pos, const Color& color = Palette::White) const;

		void overwrite(Image& dst, int32 x, int32 y) const;

		void overwrite(Image& dst, Point pos) const;

		[[nodiscard]]
		ImageROI operator ()(int32 x, int32 y, int32 w, int32 h);

		[[nodiscard]]
		ImageROI operator ()(const Point& pos, int32 w, int32 h);

		[[nodiscard]]
		ImageROI operator ()(int32 x, int32 y, const Size& size);

		[[nodiscard]]
		ImageROI operator ()(const Point& pos, const Size& size);

		[[nodiscard]]
		ImageROI operator ()(const Rect& rect);

		[[nodiscard]]
		ImageConstROI operator ()(int32 x, int32 y, int32 w, int32 h) const;

		[[nodiscard]]
		ImageConstROI operator ()(const Point& pos, int32 w, int32 h) const;

		[[nodiscard]]
		ImageConstROI operator ()(int32 x, int32 y, const Size& size) const;

		[[nodiscard]]
		ImageConstROI operator ()(const Point& pos, const Size& size) const;

		[[nodiscard]]
		ImageConstROI operator ()(const Rect& rect) const;

		[[nodiscard]]
		Polygon alphaToPolygon(uint32 threshold = 160, bool allowHoles = true) const;

		[[nodiscard]]
		Polygon alphaToPolygonCentered(uint32 threshold = 160, bool allowHoles = true) const;

		[[nodiscard]]
		MultiPolygon alphaToPolygons(uint32 threshold = 160, bool allowHoles = true) const;

		[[nodiscard]]
		MultiPolygon alphaToPolygonsCentered(uint32 threshold = 160, bool allowHoles = true) const;

		[[nodiscard]]
		Polygon grayscaleToPolygon(uint32 threshold = 160, bool allowHoles = true) const;

		[[nodiscard]]
		Polygon grayscaleToPolygonCentered(uint32 threshold = 160, bool allowHoles = true) const;

		[[nodiscard]]
		MultiPolygon grayscaleToPolygons(uint32 threshold = 160, bool allowHoles = true) const;

		[[nodiscard]]
		MultiPolygon grayscaleToPolygonsCentered(uint32 threshold = 160, bool allowHoles = true) const;

		//[[nodiscard]]
		//Array<Rect> detectObjects(HaarCascade cascade, int32 minNeighbors = 3, const Size& minSize = Size(30, 30), const Optional<Size>& maxSize = unspecified) const;

		//[[nodiscard]]
		//Array<Rect> detectObjects(HaarCascade cascade, const Array<Rect>& regions, int32 minNeighbors = 3, const Size& minSize = Size(30, 30), const Optional<Size>& maxSize = unspecified) const;

		template <class Fty, std::enable_if_t<std::disjunction_v<std::is_invocable_r<Color, Fty>, std::is_invocable_r<Color, Fty, Point>, std::is_invocable_r<Color, Fty, int32, int32>>>* = nullptr>
		static Image Generate(Size size, Fty generator);

		template <class Fty, std::enable_if_t<std::disjunction_v<std::is_invocable_r<Color, Fty, Vec2>, std::is_invocable_r<Color, Fty, double, double>>>* = nullptr>
		static Image Generate0_1(Size size, Fty generator);
	
	private:

		base_type m_data;

		uint32 m_width = 0;

		uint32 m_height = 0;
	};

	inline void swap(Image& a, Image& b) noexcept;
}

template <>
inline void std::swap(s3d::Image& a, s3d::Image& b) noexcept;

# include "detail/Image.ipp"
