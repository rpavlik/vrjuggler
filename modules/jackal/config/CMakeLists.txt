if(BUILD_JAVA)
	set(CMAKE_JAVA_INCLUDE_PATH ${TWEEK_JAVA_CLASSPATH})

	add_jar(jccl_config
		org/vrjuggler/jccl/config/Category.java
		org/vrjuggler/jccl/config/ConfigBroker.java
		org/vrjuggler/jccl/config/ConfigBrokerImpl.java
		org/vrjuggler/jccl/config/ConfigBrokerProxy.java
		org/vrjuggler/jccl/config/ConfigContext.java
		org/vrjuggler/jccl/config/ConfigDefinition.java
		org/vrjuggler/jccl/config/ConfigDefinitionRepository.java
		org/vrjuggler/jccl/config/ConfigElement.java
		org/vrjuggler/jccl/config/ConfigElementFactory.java
		org/vrjuggler/jccl/config/ConfigElementPointer.java
		org/vrjuggler/jccl/config/ConfigUndoManager.java
		org/vrjuggler/jccl/config/Configuration.java
		org/vrjuggler/jccl/config/ConfigUtilities.java
		org/vrjuggler/jccl/config/DataSource.java
		org/vrjuggler/jccl/config/DefinitionLookupException.java
		org/vrjuggler/jccl/config/event/ConfigBrokerEvent.java
		org/vrjuggler/jccl/config/event/ConfigBrokerListener.java
		org/vrjuggler/jccl/config/event/ConfigContextEvent.java
		org/vrjuggler/jccl/config/event/ConfigContextListener.java
		org/vrjuggler/jccl/config/event/ConfigDefinitionAdapter.java
		org/vrjuggler/jccl/config/event/ConfigDefinitionEvent.java
		org/vrjuggler/jccl/config/event/ConfigDefinitionListener.java
		org/vrjuggler/jccl/config/event/ConfigDefinitionRepositoryAdapter.java
		org/vrjuggler/jccl/config/event/ConfigDefinitionRepositoryEvent.java
		org/vrjuggler/jccl/config/event/ConfigDefinitionRepositoryListener.java
		org/vrjuggler/jccl/config/event/ConfigElementAdapter.java
		org/vrjuggler/jccl/config/event/ConfigElementEvent.java
		org/vrjuggler/jccl/config/event/ConfigElementListener.java
		org/vrjuggler/jccl/config/event/ConfigElementPointerEvent.java
		org/vrjuggler/jccl/config/event/ConfigElementPointerListener.java
		org/vrjuggler/jccl/config/event/ConfigEvent.java
		org/vrjuggler/jccl/config/event/ConfigListener.java
		org/vrjuggler/jccl/config/event/package.html
		org/vrjuggler/jccl/config/event/PropertyDefinitionAdapter.java
		org/vrjuggler/jccl/config/event/PropertyDefinitionEvent.java
		org/vrjuggler/jccl/config/event/PropertyDefinitionListener.java
		org/vrjuggler/jccl/config/FileDataSource.java
		org/vrjuggler/jccl/config/images/jugglerlogo.jpg
		org/vrjuggler/jccl/config/io/ConfigDefinitionConstants.java
		org/vrjuggler/jccl/config/io/ConfigDefinitionParser.java
		org/vrjuggler/jccl/config/io/ConfigDefinitionReader.java
		org/vrjuggler/jccl/config/io/ConfigDefinitionWriter.java
		org/vrjuggler/jccl/config/io/ConfigElementParser.java
		org/vrjuggler/jccl/config/io/ConfigIOConstants.java
		org/vrjuggler/jccl/config/io/ConfigSchemaResolver.java
		org/vrjuggler/jccl/config/io/ConfigurationParser.java
		org/vrjuggler/jccl/config/io/ConfigurationReader.java
		org/vrjuggler/jccl/config/io/ConfigurationWriter.java
		org/vrjuggler/jccl/config/io/DefinitionFilenameFilter.java
		org/vrjuggler/jccl/config/io/MissingAttributeException.java
		org/vrjuggler/jccl/config/io/package.html
		org/vrjuggler/jccl/config/io/ParseException.java
		org/vrjuggler/jccl/config/package.html
		org/vrjuggler/jccl/config/PropertyDefinition.java
		org/vrjuggler/jccl/config/PropertyValueDefinition.java
		org/vrjuggler/jccl/config/ResourceChooser.java
		org/vrjuggler/jccl/config/SwingWorker.java
		org/vrjuggler/jccl/config/undo/ConfigContextEdit.java
		org/vrjuggler/jccl/config/undo/ConfigElementNameEdit.java
		org/vrjuggler/jccl/config/undo/ConfigElementPropertyEdit.java
		org/vrjuggler/jccl/config/undo/ConfigElementPropertyValueAddEdit.java
		org/vrjuggler/jccl/config/undo/ConfigElementPropertyValueIndexEdit.java
		org/vrjuggler/jccl/config/undo/ConfigElementPropertyValueRemoveEdit.java
		org/vrjuggler/jccl/config/undo/package.html)
	add_dependencies(jccl_config tweek_java)
	set_target_properties(jccl_config PROPERTIES FOLDER "JCCL Java")

	# Set up custom command to copy finished jar to a more suitable place
	set(BEANDIR "${JCCL_SHARE_DIR}/beans")
	get_property(JAR TARGET jccl_config PROPERTY JAR_FILE)
	get_filename_component(JARNAME "${JAR}" NAME)
	set(DESTJAR "${CMAKE_BINARY_DIR}/${BEANDIR}/${JARNAME}")
	add_custom_command(OUTPUT "${DESTJAR}"
		COMMAND
		"${CMAKE_COMMAND}" -E copy_if_different "${JAR}" "${DESTJAR}"
		DEPENDS
		jccl_config
		COMMENT "Copying ${JARNAME} to ${BEANDIR} in build tree"
		VERBATIM)
	list(APPEND JCCL_COPIED_FILES "${DESTJAR}")
	set(JCCL_JAVA_CLASSPATH ${TWEEK_JAVA_CLASSPATH} "${DESTJAR}" CACHE INTERNAL "" FORCE)
	
	set(DESTFILE "${CMAKE_BINARY_DIR}/${BEANDIR}/jccl_config.xml")
	add_custom_command(OUTPUT "${DESTFILE}"
		COMMAND
		"${CMAKE_COMMAND}" -E copy_if_different
		"${CMAKE_CURRENT_SOURCE_DIR}/jccl_config.xml" "${DESTFILE}"
		DEPENDS
		"${CMAKE_CURRENT_SOURCE_DIR}/jccl_config.xml"
		COMMENT "Copying jccl_config.xml to ${BEANDIR} in build tree"
		VERBATIM)
	list(APPEND JCCL_COPIED_FILES "${DESTFILE}")

	# Install from our "suitable place" to its equivalent in the install tree
	install(FILES ${JCCL_COPIED_FILES}
		DESTINATION "${BEANDIR}" COMPONENT "jccl_java")

	# Add the custom meta-target to trigger the jar copying
	add_custom_target(jccl_java ALL
		DEPENDS ${JCCL_COPIED_FILES} jccl_config)
	set_target_properties(jccl_java PROPERTIES FOLDER "Convenience targets")
endif()