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
/* NOTE: This file is autogenerated, do not edit this file directly.*/

#include <TRChartsObjc/Support/RenderableInterfaceMarshaller.hh>
#include <TRChartsObjc/Support/Marshallers.hh>
#include <TRCodegenSupportObjc/Handle.hh>
#include <TRCodegenSupportObjc/BaseObject.h>


class TRChartsObjc::RenderableInterfaceMarshaller::Proxy : public Charts::Renderable
{
public:
	Proxy(const RenderableInterfaceMarshaller & marshaller, CodegenSupportObjc::StrongAnyPtr hostObject);

	virtual ~Proxy(void);

	CodegenSupportObjc::StrongAnyPtr getHostObject(void) const;

	virtual void resize(const Charts::Size & size, double contentScaleFactor);

	virtual void preUpdate(void);

	virtual bool update(void);

	virtual void preRender(void) const;

	virtual void render(void) const;

	virtual void dispose(void);

private:
	const RenderableInterfaceMarshaller & marshaller;
	mutable id __strong strongHostObject;
};



std::shared_ptr<Charts::Renderable> TRChartsObjc::RenderableInterfaceMarshaller::marshall(const CodegenSupportObjc::StrongAnyPtr & in) const
{
	if(in) {
		if([in isKindOfClass:[TRBaseObject class]]) {
			CodegenSupportObjc::Handle * const handle = static_cast<CodegenSupportObjc::Handle *>([in handle]);
			return handle->getNativeObject<Charts::Renderable>();
		} else {
			return std::make_shared<Proxy>(*this, in);
		}
	}
	return std::shared_ptr<Charts::Renderable>();
}


CodegenSupportObjc::StrongAnyPtr TRChartsObjc::RenderableInterfaceMarshaller::unmarshall(const std::shared_ptr<Charts::Renderable> & in) const
{
	if(in) {
		CodegenSupport::BaseObject * const baseObject = dynamic_cast<CodegenSupport::BaseObject *>(in.get());
		if(baseObject) {
			CodegenSupportObjc::Handle * const handle = static_cast<CodegenSupportObjc::Handle *>(baseObject->getHandle());
			return handle->getHostObject();
		} else {
			Proxy * proxy = dynamic_cast<Proxy *>(in.get());
			if(proxy) {
				return proxy->getHostObject();
			} else {
				throw std::logic_error("Cannot unmarshall");
			}
		}
	}
	return nullptr;
}


std::shared_ptr<Charts::Renderable> TRChartsObjc::RenderableInterfaceMarshaller::marshallBoxed(const id & in) const
{
	return marshall(in);
}


id TRChartsObjc::RenderableInterfaceMarshaller::unmarshallBoxed(const std::shared_ptr<Charts::Renderable> & in) const
{
	return unmarshall(in);
}

// TODO: temporary hack until we fix static init + threads problems properly

void TRChartsObjc::RenderableInterfaceMarshaller::init(void) const
{
}



TRChartsObjc::RenderableInterfaceMarshaller::Proxy::Proxy(const RenderableInterfaceMarshaller & marshaller, const CodegenSupportObjc::StrongAnyPtr hostObject)
	:marshaller(marshaller), strongHostObject(hostObject)
{
}


TRChartsObjc::RenderableInterfaceMarshaller::Proxy::~Proxy(void)
{
	// anything to verify here?
}


CodegenSupportObjc::StrongAnyPtr TRChartsObjc::RenderableInterfaceMarshaller::Proxy::getHostObject(void) const
{
	return strongHostObject;
}


void TRChartsObjc::RenderableInterfaceMarshaller::Proxy::resize(const Charts::Size & size, double contentScaleFactor)
{
	TRChartsObjc::verifyCurrentQueue();
	id<TRRenderable> target = getHostObject();
	[target resize:TRChartsObjc::getSizeMarshaller().unmarshall(size) contentScaleFactor:TRChartsObjc::getNumberMarshaller().unmarshall(contentScaleFactor)];
}


void TRChartsObjc::RenderableInterfaceMarshaller::Proxy::preUpdate(void)
{
	TRChartsObjc::verifyCurrentQueue();
	id<TRRenderable> target = getHostObject();
	[target preUpdate];
}


bool TRChartsObjc::RenderableInterfaceMarshaller::Proxy::update(void)
{
	TRChartsObjc::verifyCurrentQueue();
	id<TRRenderable> target = getHostObject();
	return TRChartsObjc::getBooleanMarshaller().marshall([target update]); 	
}


void TRChartsObjc::RenderableInterfaceMarshaller::Proxy::preRender(void) const
{
	TRChartsObjc::verifyCurrentQueue();
	id<TRRenderable> target = getHostObject();
	[target preRender];
}


void TRChartsObjc::RenderableInterfaceMarshaller::Proxy::render(void) const
{
	TRChartsObjc::verifyCurrentQueue();
	id<TRRenderable> target = getHostObject();
	[target render];
}


void TRChartsObjc::RenderableInterfaceMarshaller::Proxy::dispose(void)
{
	TRChartsObjc::verifyCurrentQueue();
	id<TRRenderable> target = getHostObject();
	[target dispose];
}
