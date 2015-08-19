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

package com.thomsonreuters.corptech.codegen;

import com.thomsonreuters.corptech.codegen.defs.DefBase;
import com.thomsonreuters.corptech.codegen.defs.OutputDef;
import com.thomsonreuters.corptech.codegen.defs.ProjectDef;
import com.thomsonreuters.corptech.codegen.defs.TopLevelDef;
import freemarker.cache.FileTemplateLoader;
import freemarker.core.Environment;
import freemarker.template.Configuration;
import freemarker.template.SimpleScalar;
import freemarker.template.Template;
import freemarker.template.TemplateException;
import org.apache.log4j.Logger;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.List;
import java.util.Map;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main
{
	private static final Logger log = Logger.getLogger(Main.class);


	public static void initGlobals(final Environment env, final DefBase model)
	{
		final Map<String, String> variables = model.resolveVariables();

		env.setGlobalVariable("cppCodegenSupportFilePrefix", new SimpleScalar("TRCodegenSupport/"));
		env.setGlobalVariable("cppCodegenSupportNamespace", new SimpleScalar("CodegenSupport"));

		env.setGlobalVariable("objcCodegenSupportFilePrefix", new SimpleScalar("TRCodegenSupportObjc/"));
		env.setGlobalVariable("objcCodegenSupportNamespace", new SimpleScalar("CodegenSupportObjc"));

		env.setGlobalVariable("cppHeaderGuardPrefix", new SimpleScalar(variables.get("cppNamespace") + "_"));
		env.setGlobalVariable("cppBaseObject", new SimpleScalar("BaseObject"));
		env.setGlobalVariable("jniCppHeaderGuardPrefix", new SimpleScalar(variables.get("jniCppNamespace") + "_"));
		env.setGlobalVariable("javaBaseObject", new SimpleScalar("BaseObject"));
		env.setGlobalVariable("objcBase", new SimpleScalar(variables.get("objcClassPrefix") + "BaseObject"));
		env.setGlobalVariable("jniPackage", new SimpleScalar(variables.get("javaPackage").replace('.', '_')));
		env.setGlobalVariable("jniClassnamePrefix", new SimpleScalar(variables.get("javaPackage").replace('.', '/') + "/"));

		for(final Map.Entry<String, String> entry : variables.entrySet()) {
			env.setGlobalVariable(entry.getKey(), new SimpleScalar(entry.getValue()));
		}
	}

	public static void outputTopLevel(final Configuration configuration, final String templateFilename, final String outputFilenamePrefix, final String outputFilenameSuffix, final List<? extends TopLevelDef> models, final boolean overwrite) throws IOException, TemplateException
	{
		for(final TopLevelDef model : models) {
			outputTopLevel(configuration, templateFilename, outputFilenamePrefix + model.getName() + outputFilenameSuffix, model, overwrite);
		}
	}

	public static void outputTopLevel(final Configuration configuration, final String templateFilename, final String outputFilename, final DefBase model, final boolean overwrite) throws IOException, TemplateException
	{
		final File file = new File(outputFilename);
		if(!overwrite) {
			if(file.exists()) {
				log.warn("Not overwriting " + file.getCanonicalPath());
				return;
			}
		}
		final Template template = configuration.getTemplate(templateFilename);
		try(final FileWriter writer = new FileWriter(file)) {
			final Environment env = template.createProcessingEnvironment(model, writer);
			initGlobals(env, model);
			env.process();
		}
	}

	public static void outputTemplates(final Configuration configuration, final ProjectDef project, final File inDir, final File outDir, final boolean overwrite) throws IOException, TemplateException
	{
		outDir.mkdirs();
		for (final File fileEntry : inDir.listFiles()) {
			final String name = fileEntry.getName();
			if(!name.startsWith("_")) {
				if (fileEntry.isDirectory()) {
					outputTemplates(configuration, project, fileEntry, new File(outDir, name), overwrite);
				} else {
					if(name.endsWith(".ftl")) {
						final String rawName = name.substring(0, name.length() - 4);
						final Pattern replacePattern = Pattern.compile("(.*?)?\\$(.*?)\\$(.*?)?");
						final Matcher matcher = replacePattern.matcher(rawName);
						if(matcher.matches()) {
							final String each = matcher.group(2);
							final String prefix = outDir.getAbsolutePath() + "/" + matcher.group(1);
							final String suffix = matcher.group(3);
							switch(each.toLowerCase()) {
								case "class":
									outputTopLevel(configuration, fileEntry.getPath(), prefix, suffix, project.getClasses(), overwrite);
									break;
								case "enum":
									outputTopLevel(configuration, fileEntry.getPath(), prefix, suffix, project.getEnums(), overwrite);
									break;
								case "interface":
									outputTopLevel(configuration, fileEntry.getPath(), prefix, suffix, project.getInterfaces(), overwrite);
									break;
								case "struct":
									outputTopLevel(configuration, fileEntry.getPath(), prefix, suffix, project.getStructs(), overwrite);
									break;
								case "templateclass":
									outputTopLevel(configuration, fileEntry.getPath(), prefix, suffix, project.getTemplateClasses(), overwrite);
									break;
								case "templateinterface":
									outputTopLevel(configuration, fileEntry.getPath(), prefix, suffix, project.getTemplateInterfaces(), overwrite);
									break;
								case "templatestruct":
									outputTopLevel(configuration, fileEntry.getPath(), prefix, suffix, project.getTemplateStructs(), overwrite);
									break;
								case "project":
									outputTopLevel(configuration, fileEntry.getPath(), prefix + project.getName() + suffix, project, overwrite);
									break;
							}
						} else {
							final String outFilename = new File(outDir, rawName).getAbsolutePath();
							outputTopLevel(configuration, fileEntry.getPath(), outFilename, project, overwrite);
						}
					}
				}
			}
		}
	}

	public static void main(final String [] args)
	{
		try {
			final ProjectDef project = ProjectDef.load("charts.xml");

			final Configuration configuration = new Configuration();
			configuration.setTemplateLoader(new FileTemplateLoader());
			//configuration.setTemplateLoader(new ClassTemplateLoader(Main.class, "/"));

			for(final OutputDef outputDef : project.getOutputs()) {
				outputTemplates(configuration, project, new File("templates/" + outputDef.getType()), new File("../" + project.getName() + "/" + outputDef.getTargetDir()), outputDef.isOverwrite());
			}

		} catch (final Exception e) {
			log.error("Error", e);
		}
	}
}
