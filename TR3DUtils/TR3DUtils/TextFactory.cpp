/*******************************************************************************
 * Copyright 2015 Thomson Reuters
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *******************************************************************************/

#include <TR3DUtils/TextFactory.hpp>
#include <TR3DUtils/RenderContext.hpp>
#include <TR3DUtils/Log.hpp>
#include <TR3DUtils/RenderTexture.hpp>
#include <TR3DUtils/Utils.hpp>

using namespace TR3DUtils;

#ifdef __APPLE__

#include <CoreText/CoreText.h>
#include <CoreFoundation/CFAttributedString.h>
#include <CoreGraphics/CoreGraphics.h>

class TextFactory::PlatformImpl
{
public:
	PlatformImpl(const std::weak_ptr<RenderContext> & context);

	~PlatformImpl(void);

	void drawText(const glm::mat4 & modelViewProjection, const std::string & text, const std::string & fontName, size_t fontSize, const glm::vec3 & position, glm::float_t rotation, const glm::vec4 & margin, const glm::vec2 & align, const glm::vec4 & color, glm::float_t scale);

	CFDictionaryRef getAttributesForSizedFont(const std::string & fontName, size_t fontSize);

	CFMutableAttributedStringRef createAttributedString(const std::string & text, const std::string & fontName, size_t fontSize);

	CGContextRef createContextFromString(const std::string & text, const std::string & fontName, size_t fontSize);

	bool uploadData(const std::shared_ptr<RenderTexture> & target, const std::string & text, const std::string & fontName, size_t fontSize, const glm::vec2 & size);

private:
    typedef std::tuple<std::string, size_t> FontKey;
    
	CTParagraphStyleRef paragraphStyle;

	CGColorSpaceRef colorspace;

	CGColorRef color;

	std::map<FontKey, CFDictionaryRef> attributesForSizedFont;

	const std::weak_ptr<RenderContext> context;
};

#else
#ifdef __ANDROID_API__

#include <jni.h>

class TextFactory::PlatformImpl
{
public:
	PlatformImpl(const std::weak_ptr<RenderContext> & context);

	bool uploadData(const std::shared_ptr<RenderTexture> & target, const std::string & text, const std::string & fontName, size_t fontSize, const glm::vec2 & size);

private:
	bool inited;
	jclass clsTextRenderer;
	jmethodID midGenerateAndUploadTexture;

	const std::weak_ptr<RenderContext> context;
};

#else

class TextFactory::PlatformImpl
{
public:
	PlatformImpl(const std::weak_ptr<RenderContext> & context);

	bool uploadData(const std::shared_ptr<RenderTexture> & target, const std::string & text, const std::string & fontName, size_t fontSize, const glm::vec2 & size);

private:
	const std::weak_ptr<RenderContext> context;
};

#endif
#endif

#ifdef __APPLE__

namespace
{
	const glm::vec2 vertexPositions[6] = {
		glm::vec2 {0.0f, 0.0f},
		glm::vec2 {1.0f, 0.0f},
		glm::vec2 {0.0f, 1.0f},
		glm::vec2 {0.0f, 1.0f},
		glm::vec2 {1.0f, 0.0f},
		glm::vec2 {1.0f, 1.0f}
	};
}

TextFactory::PlatformImpl::PlatformImpl(const std::weak_ptr<RenderContext> & context)
:context(context)
{
	colorspace = CGColorSpaceCreateDeviceRGB();
    const CGFloat components[] = {1.f, 1.f, 1.f, 1.f};
	color = CGColorCreate(colorspace, components);
	const GLuint numStyles = 2;
	const CGFloat lineHeightMultiple = 1.0f;
	const CTTextAlignment alignment = kCTLeftTextAlignment;
	CTParagraphStyleSetting settings[numStyles] =
	{
		{
			kCTParagraphStyleSpecifierAlignment,
			sizeof(alignment),
			&alignment
		},
		{
			kCTParagraphStyleSpecifierLineHeightMultiple,
			sizeof(lineHeightMultiple),
			&lineHeightMultiple
		}
	};
	paragraphStyle = CTParagraphStyleCreate(settings, numStyles);
}

TextFactory::PlatformImpl::~PlatformImpl(void)
{
	CFRelease(colorspace);
	CFRelease(color);
	CFRelease(paragraphStyle);
	for(const auto & i : attributesForSizedFont) {
		CFRelease(i.second);
	}
}

CFDictionaryRef TextFactory::PlatformImpl::getAttributesForSizedFont(const std::string & fontName, const size_t fontSize)
{
	const auto key = std::make_tuple(fontName, fontSize);
	const auto & iter = attributesForSizedFont.find(key);
	if(iter == attributesForSizedFont.end()) {
		CFDictionaryRef attributes = nullptr;
		if(const CFStringRef cfFontName = CFStringCreateWithCString(kCFAllocatorDefault, fontName.c_str(), kCFStringEncodingUTF8)) {
			if(const CTFontRef font = CTFontCreateWithName(cfFontName, (float)fontSize, NULL)) {
				const GLuint dictionarySize = 3;
				const CFStringRef keys[dictionarySize] =
				{
					kCTParagraphStyleAttributeName,
					kCTFontAttributeName,
					kCTForegroundColorAttributeName
				};
				const CFTypeRef values[dictionarySize] =
				{
					paragraphStyle,
					font,
					color
				};
				attributes = CFDictionaryCreate(NULL, (const void **)&keys, (const void **)&values, dictionarySize, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
				CFRelease(font);
			}
			CFRelease(cfFontName);
		}
		attributesForSizedFont[key] = attributes;
		return attributes;
	} else {
		return iter->second;
	}
}

CFMutableAttributedStringRef TextFactory::PlatformImpl::createAttributedString(const std::string & text, const std::string & fontName, const size_t fontSize)
{
	CFMutableAttributedStringRef result = nullptr;
	if(const CFStringRef cfText = CFStringCreateWithCString(kCFAllocatorDefault, text.c_str(), kCFStringEncodingUTF8)) {
		const CFDictionaryRef attributes = getAttributesForSizedFont(fontName, fontSize);
		if(const CFMutableAttributedStringRef attrString = CFAttributedStringCreateMutable(kCFAllocatorDefault, 0)) {
			CFAttributedStringReplaceString(attrString, CFRangeMake(0, 0), cfText);
			const CFRange range = CFRangeMake(0, CFAttributedStringGetLength(attrString));
			CFAttributedStringSetAttributes(attrString, range, attributes, FALSE);
			result = attrString;
		}
		CFRelease(cfText);
	}
	return result;
}

CGContextRef TextFactory::PlatformImpl::createContextFromString(const std::string & text, const std::string & fontName, const size_t fontSize)
{
	CGContextRef result = NULL;
	if(const CFMutableAttributedStringRef attrString = createAttributedString(text, fontName, fontSize)) {
		if(const CTFramesetterRef frameSetter = CTFramesetterCreateWithAttributedString(attrString)) {
			if(const CGMutablePathRef path = CGPathCreateMutable()) {
				const CFRange range = CFRangeMake(0, CFAttributedStringGetLength(attrString));
				CFRange actualRange;
				CGSize constraint = CGSizeMake(CGFLOAT_MAX, CGFLOAT_MAX);
				const CGSize size = CTFramesetterSuggestFrameSizeWithConstraints(frameSetter, range, NULL, constraint, &actualRange);
				const CGRect bounds = CGRectMake(0.0f, 0.0f, size.width, size.height);
				CGPathAddRect(path, NULL, bounds);
				if(const CTFrameRef frame = CTFramesetterCreateFrame(frameSetter, actualRange, path, NULL)) {
					const size_t width = (size_t)size.width;
					const size_t height = (size_t)size.height;
					const size_t stride = width * 4;
					if(const CGContextRef context = CGBitmapContextCreate(NULL, width, height, 8, stride, colorspace, kCGImageAlphaPremultipliedLast)) {
						CGContextTranslateCTM(context, 0.0, height);
						CGContextScaleCTM(context, 1.0, -1.0);
						CTFrameDraw(frame, context);
						CGContextFlush(context);
						result = context;
					}
					CFRelease(frame);
				}
				CFRelease(path);
			}
			CFRelease(frameSetter);
		}
		CFRelease(attrString);
	}
	return result;
}

bool TextFactory::PlatformImpl::uploadData(const std::shared_ptr<RenderTexture> & texture, const std::string & text, const std::string & fontName, const size_t fontSize, const glm::vec2 & size)
{
	bool status = false;
	if(const CGContextRef context = createContextFromString(text, fontName, fontSize)) {
		const GLsizei width = GLsizei(CGBitmapContextGetWidth(context));
		const GLsizei height = GLsizei(CGBitmapContextGetHeight(context));
		const GLvoid * const pixels = CGBitmapContextGetData(context);
		Log::Trace("Uploading text texture \"%s\" (W:%d H:%d)", text.c_str(), width, height);
		texture->uploadData(GL_RGBA, GL_UNSIGNED_BYTE, width, height, pixels);
		status = true;
		CFRelease(context);
	}
	return status;
}

#else
#ifdef __ANDROID_API__

namespace TRChartsJNI
{
	namespace Utils
	{
		JNIEnv * getThreadEnv(void);
	}
}

TextFactory::PlatformImpl::PlatformImpl(const std::weak_ptr<RenderContext> & context)
		: context(context), inited(false), clsTextRenderer(nullptr), midGenerateAndUploadTexture(0)
{
}

bool TextFactory::PlatformImpl::uploadData(const std::shared_ptr<RenderTexture> & texture, const std::string & text, const std::string & fontName, const size_t fontSize, const glm::vec2 & size)
{
	JNIEnv * const env = TRChartsJNI::Utils::getThreadEnv();

	if(!inited) {
		const char * const className = "com/thomsonreuters/corptech/tr3dutils/TRChartsTextRenderer";
		const char * const methodName = "generateAndUploadTexture";
		const char * const methodSignature = "(Ljava/lang/String;Ljava/lang/String;JJ)J";

		TR3DUtils::Log::Warn("Finding class");
		const jclass cls = env->FindClass(className);
		if(TR_VERIFY(cls)) {
			clsTextRenderer = (jclass)env->NewGlobalRef(cls);
		}
		midGenerateAndUploadTexture = TR_VERIFY(env->GetStaticMethodID(clsTextRenderer, methodName, methodSignature));

		inited = true;
	}

	if(TR_VERIFY(clsTextRenderer && midGenerateAndUploadTexture)) {

		const jstring kText = env->NewStringUTF(text.c_str());
		const jstring kFontName = env->NewStringUTF( fontName.c_str());
		const jlong kTextSize = jlong(fontSize);
		const jlong kTextureID = jlong(texture->getTextureId());

		const int64_t sizes = env->CallStaticLongMethod(clsTextRenderer, midGenerateAndUploadTexture, kText, kFontName, kTextSize, kTextureID);

		if (sizes > 0){
			const int32_t width = (sizes >> 16) & 0xFFFF;
			const int32_t height = sizes & 0xFFFF;
			texture->setSize(glm::vec2(width, height));
			return true;
		}
	}

	return false;
}

#else

TextFactory::PlatformImpl::PlatformImpl(const std::weak_ptr<RenderContext> & context)
		: context(context)
{
	TR3DUtils::Log::Error("No text rendering implementation available for this platform");
}

bool TextFactory::PlatformImpl::uploadData(const std::shared_ptr<RenderTexture> & texture, const std::string & text, const std::string & fontName, const size_t fontSize, const glm::vec2 & size)
{
	return nullptr;
}

#endif
#endif


TextFactory::TextFactory(const std::weak_ptr<RenderContext> & context)
		: context(context), platformImpl(new PlatformImpl(context))
{
}

TextFactory::~TextFactory(void)
{
}

std::shared_ptr<RenderTexture> TextFactory::createTextTexture(const std::string & text, const std::string & fontName, size_t fontSize) const
{
	const std::shared_ptr<RenderContext> context = this->context.lock();
	if(TR_VERIFY(context)) {
        const std::shared_ptr<RenderTexture> texture = context->createTexture();
        texture->setWrapping(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
        texture->setFiltering(GL_LINEAR, GL_LINEAR);
        platformImpl->uploadData(texture, text, fontName, fontSize, glm::vec2(FLT_MAX, FLT_MAX));
        return texture;
    } else {
        return nullptr;
    }
}
