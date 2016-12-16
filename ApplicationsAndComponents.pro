TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS += \
    PugiXML \
    PresentationModel \
    PreDestroy \
    SqlDataWidget_EntryMapper \
    WorkLogger

#note: using this setup mandates that .pro file name matches enclosing folder
PugiXML.subdir = 3rd-Party/PugiXML
PresentationModel.subdir = Components/PresentationModel
PreDestroy.subdir = Components/PreDestroy
SqlDataWidget_EntryMapper.subdir = Components/SqlDataWidget_EntryMapper
WorkLogger.subdir = Applications/WorkLogger

WorkLogger.depends = PresentationModel
WorkLogger.depends = SqlDataWidget_EntryMapper
