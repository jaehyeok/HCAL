
import FWCore.ParameterSet.Config as cms
process = cms.Process('Test')

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 100

RUNNUMBER = 254743
print "Running on: " + str(RUNNUMBER)                           

process.source = cms.Source("HcalTBSource",
  fileNames = cms.untracked.vstring(
"file:root://eoscms.cern.ch//eos/cms/store/group/dpg_hcal/comm_hcal/LS1/USC_254730.root",
"file:root://eoscms.cern.ch//eos/cms/store/group/dpg_hcal/comm_hcal/LS1/USC_254743.root"
)
)
 
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(False),
#    SkipEvent = cms.untracked.vstring('ProductNotFound')
)

#process.unpacker = cms.EDProducer("HcalTBObjectUnpacker",
#    HcalTriggerFED       = cms.untracked.int32(1),
#    HcalSlowDataFED      = cms.untracked.int32(3),
#    HcalTDCFED           = cms.untracked.int32(-1),
#    HcalSourcePosFED     = cms.untracked.int32(-1),
#    IncludeUnmatchedHits = cms.untracked.bool(False)
#)



process.hcalDigis = cms.EDProducer("HcalRawToDigi",
    ###UnpackHF = cms.untracked.bool(True),
    ### Flag to enable unpacking of TTP channels (default = false)
    ###UnpackTTP = cms.untracked.bool(True),
    FilterDataQuality = cms.bool(False),
    ###HcalFirstFED = cms.untracked.int32(700),
    ###InputLabel = cms.InputTag("rawDataCollector"),
    InputLabel = cms.InputTag("source"),
    ComplainEmptyData = cms.untracked.bool(False),
    UnpackCalib = cms.untracked.bool(True),
    ###FEDs = cms.untracked.vint32(
    ###    700, 701, 702, 703, 704,
    ###    705, 706, 707, 708, 709,
    ###    710, 711, 712, 713, 714,
    ###    715, 716, 717, 718, 719,
    ###    720, 721, 722, 723, 724,
    ###    725, 726, 727, 728, 729,
    ###    730, 731, 732),
    lastSample = cms.int32(9),
    firstSample = cms.int32(0)
)




# Add your analyzer here:
process.Analyzer = cms.EDAnalyzer("HFuxc",
# hcalDigiTag = cms.untracked.InputTag('hcalDigis')
)



outfile="./Run_"+str(RUNNUMBER)+".root"
process.TFileService = cms.Service("TFileService",
    fileName = cms.string(outfile),
    closeFileFast = cms.untracked.bool(True)
) 


##process.load("EventFilter.HcalRawToDigi.HcalRawToDigi_cfi")
process.load("Configuration.Geometry.GeometryIdeal_cff") 
###process.load("Configuration.StandardSequences.RawToDigi_Data_cff")
process.load("RecoLocalCalo.Configuration.hcalLocalReco_cff")
#process.load("RecoLocalCalo.HcalRecProducers.HcalSimpleReconstructor_hf_cfi")


process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '74X_dataRun2_HLT_v1', '') # 2015C

#------------------------------------------------------------
# Define paths: DIGI, RECO
#------------------------------------------------------------

#process.DIGI = cms.Path(process.hcalDigis )
#process.RECO = cms.Path(process.hfreco )



##process.p = cms.Path(process.hcalDigis * process.hfreco)
process.p = cms.Path(process.hcalDigis*process.hfreco*process.Analyzer)
##process.p = cms.Path(process.hcalDigis*process.Analyzer)
##process.p = cms.Path(process.Analyzer)
##process.p = cms.Path(process.hcalDigis)

