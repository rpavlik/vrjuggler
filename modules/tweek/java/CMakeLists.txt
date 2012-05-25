foreach(idlname ${TWEEK_IDL_NAMES})
	java_idlj(TWEEK_IDL_JAVA "${TWEEK_IDL_DIR}/${idlname}.idl" -i "${CMAKE_CURRENT_SOURCE_DIR}/..")
endforeach()

#file(GLOB_RECURSE TWEEK_IDL_JAVA ${CMAKE_CURRENT_BINARY_DIR}/tweek/*.java)

if(APPLE)
	set(TWEEK_MAC_SRC org/vrjuggler/tweek/mac/TweekAppListener.java)
else()
	set(TWEEK_MAC_SRC)
endif()

set(EXTERNALS "${CMAKE_CURRENT_SOURCE_DIR}/../../../external")
find_jar(JDOM_JAR
	jdom
	PATHS
	${EXTERNALS}/jdom/build)

find_jar(JAXENCORE_JAR
	jaxen-core
	PATHS
	${EXTERNALS}/jdom/lib)
find_jar(JAXENJDOM_JAR
	jaxen-jdom
	PATHS
	${EXTERNALS}/jdom/lib)
find_jar(SAXPATH_JAR
	saxpath
	PATHS
	${EXTERNALS}/jdom/lib)
find_jar(XERXES_JAR
	xerces
	PATHS
	${EXTERNALS}/jdom/lib)
find_jar(XMLAPIS_JAR
	xml-apis
	PATHS
	${EXTERNALS}/jdom/lib)

set(JDOM_JARS
	"${JDOM_JAR}"
	"${JAXENCORE_JAR}"
	"${JAXENJDOM_JAR}"
	"${SAXPATH_JAR}"
	"${XERXES_JAR}"
	"${XMLAPIS_JAR}")
find_jar(LIQUIDLNF_JAR
	liquidlnf
	PATHS
	${EXTERNALS}/swing-laf/liquid/)
find_jar(METOUIA_JAR
	metouia
	PATHS
	${EXTERNALS}/swing-laf/metouia/)
find_jar(JGOODIESLOOKS_JAR
	looks
	PATHS
	${EXTERNALS}/swing-laf/jgoodies-looks/)

set(CMAKE_JAVA_INCLUDE_PATH ${JDOM_JARS} "${LIQUIDLNF_JAR}" "${METOUIA_JAR}" "${JGOODIESLOOKS_JAR}")

#set(CMAKE_JAVA_TARGET_OUTPUT_DIR "${CMAKE_BINARY_DIR}/${TWEEK_SHARE_DIR}/java")
# add_jar(Tweek
	# org/vrjuggler/tweek/EnvironmentServiceImpl.java
	# org/vrjuggler/tweek/GlobalPreferencesServiceImpl.java
	# org/vrjuggler/tweek/Tweek.java
	# org/vrjuggler/tweek/TweekCore.java
	# org/vrjuggler/tweek/gui/AboutBox.java
	# org/vrjuggler/tweek/gui/BeanContainer.java
	# org/vrjuggler/tweek/gui/BeanPrefsDialog.java
	# org/vrjuggler/tweek/gui/BeanStatusDialog.java
	# org/vrjuggler/tweek/gui/DirectConnectionDialog.java
	# org/vrjuggler/tweek/gui/DisconnectionDialog.java
	# org/vrjuggler/tweek/gui/GlobalPrefsUpdateEvent.java
	# org/vrjuggler/tweek/gui/GlobalPrefsUpdateListener.java
	# org/vrjuggler/tweek/gui/MessagePanel.java
	# org/vrjuggler/tweek/gui/NamingServiceConnectionDialog.java
	# org/vrjuggler/tweek/gui/PrefsDialog.java
	# org/vrjuggler/tweek/gui/SubjectManagerWrapper.java
	# org/vrjuggler/tweek/gui/TweekFrame.java
	# org/vrjuggler/tweek/gui/bulb-off-small.gif
	# org/vrjuggler/tweek/gui/bulb-on-small.gif
	# org/vrjuggler/tweek/gui/tweek-icon.gif
	# org/vrjuggler/tweek/gui/tweek.gif
	# org/vrjuggler/tweek/text/MessageAdditionEvent.java
	# org/vrjuggler/tweek/text/MessageAdditionListener.java
	# org/vrjuggler/tweek/text/MessageDocument.java
	# org/vrjuggler/tweek/text/error.gif
	# org/vrjuggler/tweek/text/status.gif
	# org/vrjuggler/tweek/text/warning.gif
	# ${TWEEK_MAC_SRC}
	# LICENSE-java-laf.txt)

add_jar(TweekBeans org/vrjuggler/tweek/beans/BeanAttributes.java
	org/vrjuggler/tweek/beans/BeanDependency.java
	org/vrjuggler/tweek/beans/BeanDependencyManager.java
	org/vrjuggler/tweek/beans/BeanFocusChangeEvent.java
	org/vrjuggler/tweek/beans/BeanFocusChangeListener.java
	org/vrjuggler/tweek/beans/BeanInstantiationCommunicator.java
	org/vrjuggler/tweek/beans/BeanInstantiationEvent.java
	org/vrjuggler/tweek/beans/BeanInstantiationListener.java
	org/vrjuggler/tweek/beans/BeanModelViewer.java
	org/vrjuggler/tweek/beans/BeanPathException.java
	org/vrjuggler/tweek/beans/BeanPreferences.java
	org/vrjuggler/tweek/beans/BeanRegistrationEvent.java
	org/vrjuggler/tweek/beans/BeanRegistrationListener.java
	org/vrjuggler/tweek/beans/BeanRegistry.java
	org/vrjuggler/tweek/beans/BeanTreeModel.java
	org/vrjuggler/tweek/beans/BestSAXChecker.java
	org/vrjuggler/tweek/beans/ClipboardUser.java
	org/vrjuggler/tweek/beans/DefaultBeanModelViewer.java
	org/vrjuggler/tweek/beans/FileFinder.java
	org/vrjuggler/tweek/beans/FileLoader.java
	org/vrjuggler/tweek/beans/GenericBean.java
	org/vrjuggler/tweek/beans/HelpProvider.java
	org/vrjuggler/tweek/beans/JarDependency.java
	org/vrjuggler/tweek/beans/PanelBean.java
	org/vrjuggler/tweek/beans/ServiceBean.java
	org/vrjuggler/tweek/beans/TweekBean.java
	org/vrjuggler/tweek/beans/UndoHandler.java
	org/vrjuggler/tweek/beans/ViewerBean.java
	org/vrjuggler/tweek/beans/XMLBeanFinder.java
	org/vrjuggler/tweek/beans/loader/BeanInstantiationException.java
	org/vrjuggler/tweek/beans/loader/BeanJarClassLoader.java
	org/vrjuggler/tweek/beans/loader/BeanJarFile.java
	org/vrjuggler/tweek/beans/loader/BeanLoader.java)

add_jar(TweekEvents
	org/vrjuggler/tweek/event/EventListenerRegistry.java
	org/vrjuggler/tweek/event/FileActionEvent.java
	org/vrjuggler/tweek/event/FileActionGenerator.java
	org/vrjuggler/tweek/event/FileActionListener.java
	org/vrjuggler/tweek/event/RegistrationEvent.java
	org/vrjuggler/tweek/event/RegistrationListener.java
	org/vrjuggler/tweek/event/TweekFrameAdapter.java
	org/vrjuggler/tweek/event/TweekFrameEvent.java
	org/vrjuggler/tweek/event/TweekFrameListener.java
	org/vrjuggler/tweek/event/UndoActionEvent.java
	org/vrjuggler/tweek/event/UndoActionGenerator.java
	org/vrjuggler/tweek/event/UndoActionListener.java
	org/vrjuggler/tweek/event/UserLevelChangeEvent.java
	org/vrjuggler/tweek/event/UserLevelChangeListener.java)

add_jar(TweekNet
	org/vrjuggler/tweek/net/CommunicationEvent.java
	org/vrjuggler/tweek/net/CommunicationListener.java
	org/vrjuggler/tweek/net/corba/CorbaService.java
	${TWEEK_IDL_JAVA})

get_property(TWEEKNET_JAR TARGET TweekNet PROPERTY JAR_FILE)

get_property(TWEEKBEANS_JAR TARGET TweekBeans PROPERTY JAR_FILE)
list(APPEND CMAKE_JAVA_INCLUDE_PATH "${TWEEKNET_JAR}" "${TWEEKBEANS_JAR}")
add_jar(TweekBeanDelivery
	org/vrjuggler/tweek/beandelivery/BeanDeliveryObserverImpl.java
	org/vrjuggler/tweek/beandelivery/BeanDeliverySubjectUpdateEvent.java
	org/vrjuggler/tweek/beandelivery/BeanDeliverySubjectUpdateListener.java
	org/vrjuggler/tweek/beandelivery/TweekBeanIntrospector.java)
add_dependencies(TweekBeanDelivery TweekNet TweekBeans)
	
add_jar(TweekServices
	org/vrjuggler/tweek/services/EnvironmentService.java
	org/vrjuggler/tweek/services/EnvironmentServiceProxy.java
	org/vrjuggler/tweek/services/ExtensionFileFilter.java
	org/vrjuggler/tweek/services/GlobalPreferencesService.java
	org/vrjuggler/tweek/services/GlobalPreferencesServiceProxy.java)

#set(CMAKE_JAVA_TARGET_OUTPUT_DIR "${CMAKE_BINARY_DIR}/${TWEEK_SHARE_DIR}/beans")
add_jar(Viewers
	org/vrjuggler/tweek/treeviewer/BeanSelectionListener.java
	org/vrjuggler/tweek/treeviewer/BeanTree.java
	org/vrjuggler/tweek/treeviewer/BeanTreeViewer.java
	org/vrjuggler/tweek/iconviewer/BeanIconPanel.java
	org/vrjuggler/tweek/iconviewer/BeanIconViewer.java
	org/vrjuggler/tweek/iconviewer/InternalBeanFrame.java
	org/vrjuggler/tweek/iconviewer/PrefsEditor.java
	org/vrjuggler/tweek/iconviewer/PrefsEvent.java
	org/vrjuggler/tweek/iconviewer/PrefsEventListener.java
	org/vrjuggler/tweek/iconviewer/back-small.gif
	org/vrjuggler/tweek/iconviewer/back.gif
	org/vrjuggler/tweek/iconviewer/bean_default.gif
	org/vrjuggler/tweek/iconviewer/bean_folder.gif
	org/vrjuggler/tweek/iconviewer/forward-small.gif
	org/vrjuggler/tweek/iconviewer/forward.gif
	org/vrjuggler/tweek/iconviewer/home-small.gif
	org/vrjuggler/tweek/iconviewer/home.gif
	LICENSE-java-laf.txt)