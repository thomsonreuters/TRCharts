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

#include <TRChartsObjc/Support/AxisLayoutInterfaceMarshaller.hh>
#include <TRChartsObjc/Support/Marshallers.hh>
#include <TRCodegenSupportObjc/Handle.hh>
#include <TRCodegenSupportObjc/BaseObject.h>


class TRChartsObjc::AxisLayoutInterfaceMarshaller::Proxy : public Charts::AxisLayout
{
public:
	Proxy(const AxisLayoutInterfaceMarshaller & marshaller, CodegenSupportObjc::StrongAnyPtr hostObject);

	virtual ~Proxy(void);

	CodegenSupportObjc::StrongAnyPtr getHostObject(void) const;

	virtual Charts::DataTransform calculateTransform(const std::shared_ptr<Charts::ContinuousAxis> & axis, const Charts::Range & dataRange, double screenLength, const Charts::DataTransform & renderTransform) const;

private:
	const AxisLayoutInterfaceMarshaller & marshaller;
	mutable id __strong strongHostObject;
};



std::shared_ptr<Charts::AxisLayout> TRChartsObjc::AxisLayoutInterfaceMarshaller::marshall(const CodegenSupportObjc::StrongAnyPtr & in) const
{
	if(in) {
		if([in isKindOfClass:[TRBaseObject class]]) {
			CodegenSupportObjc::Handle * const handle = static_cast<CodegenSupportObjc::Handle *>([in handle]);
			return handle->getNativeObject<Charts::AxisLayout>();
		} else {
			return std::make_shared<Proxy>(*this, in);
		}
	}
	return std::shared_ptr<Charts::AxisLayout>();
}


CodegenSupportObjc::StrongAnyPtr TRChartsObjc::AxisLayoutInterfaceMarshaller::unmarshall(const std::shared_ptr<Charts::AxisLayout> & in) const
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


std::shared_ptr<Charts::AxisLayout> TRChartsObjc::AxisLayoutInterfaceMarshaller::marshallBoxed(const id & in) const
{
	return marshall(in);
}


id TRChartsObjc::AxisLayoutInterfaceMarshaller::unmarshallBoxed(const std::shared_ptr<Charts::AxisLayout> & in) const
{
	return unmarshall(in);
}

// TODO: temporary hack until we fix static init + threads problems properly

void TRChartsObjc::AxisLayoutInterfaceMarshaller::init(void) const
{
}



TRChartsObjc::AxisLayoutInterfaceMarshaller::Proxy::Proxy(const AxisLayoutInterfaceMarshaller & marshaller, const CodegenSupportObjc::StrongAnyPtr hostObject)
	:marshaller(marshaller), strongHostObject(hostObject)
{
}


TRChartsObjc::AxisLayoutInterfaceMarshaller::Proxy::~Proxy(void)
{
	// anything to verify here?
}


CodegenSupportObjc::StrongAnyPtr TRChartsObjc::AxisLayoutInterfaceMarshaller::Proxy::getHostObject(void) const
{
	return strongHostObject;
}


Charts::DataTransform TRChartsObjc::AxisLayoutInterfaceMarshaller::Proxy::calculateTransform(const std::shared_ptr<Charts::ContinuousAxis> & axis, const Charts::Range & dataRange, double screenLength, const Charts::DataTransform & renderTransform) const
{
	TRChartsObjc::verifyCurrentQueue();
	id<TRAxisLayout> target = getHostObject();
	return TRChartsObjc::getDataTransformMarshaller().marshall([target calculateTransform:TRChartsObjc::getContinuousAxisMarshaller().unmarshall(axis) dataRange:TRChartsObjc::getRangeMarshaller().unmarshall(dataRange) screenLength:TRChartsObjc::getNumberMarshaller().unmarshall(screenLength) renderTransform:TRChartsObjc::getDataTransformMarshaller().unmarshall(renderTransform)]); 	
}

