
IABEXENAME=iAB.exe

IDIR ="./common/:./LucidApplicationBuilder/"

ifeq ($(origin CC), default)
CC = g++
endif

ifeq ($(origin LL), undefined)
LL = $(CC)
endif


CPPFLAGS:=$(shell ./contrib/wxWidgets-2.8.12/gtk-build-inx/wx-config --cppflags) -std=c++11 -I./common/ -I./LucidApplicationBuilder/
ALLCFLAGS=$(CPPFLAGS)



#@echo $(CPPFLAGS)

LDFLAGS:=$(shell ./contrib/wxWidgets-2.8.12/gtk-build-inx/wx-config --libs)

ODIR=obj
LDIR =../lib

LIBS=

#extra deps here!
#_DEPS = 

DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

# Dialog boxes todo
# common/EHSParamsDialog.o \
# common/FolderDlg.o \
# common/HScrollListBox.o \
# common/TransferErrorDlog.o \
# common/TransferToTargetDialog.o \


_OBJ =  common/bmpfile.o \
common/common.o \
common/EHSInitParams.o \
common/ExtBdfFile.o \
common/ExtBmpFile.o \
common/ExtDataFile.o \
common/ExtFile.o \
common/ExtGuiFile.o \
common/ExtNlsFile.o \
common/ExtPngFile.o \
common/ExtResourceFile.o \
common/ExtTransferableFile.o \
common/GlobalFuncs_1.o \
common/GlobalFuncs_2.o \
common/GuiWidget.o \
common/LabLgbBaseApp.o \
common/LccPmdXfers.o \
common/LccTimeStamp.o \
common/Log.o \
common/LucidRegAccess.o \
common/LucidString.o \
common/LucidTcpipClient.o \
common/LucidTcpipClientDlg.o \
common/Markup.o \
common/ProjectMetaDataChecks.o \
common/ProjectMetaData.o \
common/ProjectMetaDataIO.o \
common/ProjFolderMinder.o \
common/ResizingDialog.o \
common/RevisionGuru.o \
common/ScreenTagDescripEditor.o \
common/ScreenTagDialog.o \
common/TgtTransProgDlog.o \
common/Trigs.o \
LucidApplicationBuilder/BlockOperations.o \
LucidApplicationBuilder/ChildFrame.o \
LucidApplicationBuilder/ComponentMenuItem.o \
LucidApplicationBuilder/ConDataTempStore.o \
LucidApplicationBuilder/Condat.o \
LucidApplicationBuilder/Debugger.o \
LucidApplicationBuilder/DEP.o \
LucidApplicationBuilder/DrawProg.o \
LucidApplicationBuilder/DrawProgDoc.o \
LucidApplicationBuilder/DrawProgView.o \
LucidApplicationBuilder/Encapsulate.o \
LucidApplicationBuilder/Encapsulation.o \
LucidApplicationBuilder/explorer1.o \
LucidApplicationBuilder/FileOperations.o \
LucidApplicationBuilder/FSM.o \
LucidApplicationBuilder/FunctionBlockTree.o \
LucidApplicationBuilder/Group.o \
LucidApplicationBuilder/IconLines.o \
LucidApplicationBuilder/IconParams.o \
LucidApplicationBuilder/LucidApplicationBuilder.o \
LucidApplicationBuilder/MainFrame.o \
LucidApplicationBuilder/MyTreeCtrl.o \
LucidApplicationBuilder/Parameter.o \
LucidApplicationBuilder/ParameterStore.o \
LucidApplicationBuilder/port.o \
LucidApplicationBuilder/proc_function.o \
LucidApplicationBuilder/ProjectBar.o \
LucidApplicationBuilder/Project.o \
LucidApplicationBuilder/ProjectDialog.o \
LucidApplicationBuilder/tagdialog.o \
LucidApplicationBuilder/TypeConversion.o 

OBJ = $(_OBJ)
#$(patsubst %,$(ODIR)/%,$(_OBJ))

.PHONY: all


all: $(OBJ)
	$(LL) -o $(IABEXENAME) $^ $(LIBS)

print:
	@echo $(ALLCFLAGS)
	@echo $(LIBS)
	@echo $(IABEXENAME)


$(ODIR)/%.o: %.o \ 
	@mkdir -p $(@D)
	$(CC) -c -o $@ $< $(ALLCFLAGS) -I$(IDIR)

$(ODIR)/%.o :  $(DEPS)


.PHONY: clean

clean:
	rm -f $(IABEXENAME) PSD $(ODIR)/*.o *~ core




