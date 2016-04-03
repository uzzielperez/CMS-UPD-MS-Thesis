from FWCore.ParameterSet.VarParsing import VarParsing
import FWCore.ParameterSet.Config as cms

options = VarParsing ('python')

options.register('globalTag',
                     '76X_mcRun2_asymptotic_v12',
                     VarParsing.multiplicity.singleton,
                     VarParsing.varType.string,
                     "global tag to use when running"
                 
                    )

options.setDefault('maxEvents', 100)
options.parseArguments()


#================ PROCESS 

#process = cms.Process("FirstExoDiphoton")
#plug-in in EDM Framework
process = cms.Process("ExoDiphoton")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(options.maxEvents) )

#Dataset/File input
process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'root://cmsxrootd.fnal.gov//store/mc/RunIIFall15MiniAODv2/RSGravToGG_kMpl-001_M-1500_TuneCUEP8M1_13TeV-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/50000/34B117D8-C1B8-E511-B935-782BCB20EDD2.root'
    )
)

# for global tag
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = options.globalTag

# geometry for saturation
process.load("Configuration.StandardSequences.GeometryDB_cff")

# for output fileprocess.TFileService = cms.Service(
process.TFileService = cms.Service(
    "TFileService",
    fileName = cms.string("ExoDiphotonNtuple.root")
     )


#======= VID for EGM ID 
from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
switchOnVIDPhotonIdProducer(process, DataFormat.MiniAOD)
# define which IDs we want to produce
my_id_modules = ['RecoEgamma.PhotonIdentification.Identification.cutBasedPhotonID_Spring15_25ns_V1_cff']
#add them to the VID producer
for idmod in my_id_modules:
  setupAllVIDIdsInModule(process,idmod,setupVIDPhotonSelection)

  

#=============== MAIN ANALYZER 
#process.demo = cms.EDAnalyzer('ExoAnalyzer')
process.diphoton = cms.EDAnalyzer('ExoDiPhotonRSGSignalAnalyzer',
    #genParticle tag
    #genParticlesMiniAOD = cms.InputTag("prunedGenParticles"),
   
    #ALL INPUT TAGs
     # photon tag
     photonsMiniAOD = cms.InputTag("slimmedPhotons"),
     # genParticle tag
     genParticlesMiniAOD = cms.InputTag("prunedGenParticles"),
     # ak4 jets
     jetsMiniAOD = cms.InputTag("slimmedJets"),
     jetPtThreshold = cms.double(30.),
     jetEtaThreshold = cms.double(2.5),


    # rho tag (use fixedGridRhoAll?)
    rho = cms.InputTag("fixedGridRhoFastjetAll"),
    # EGM eff. areas
    effAreaChHadFile = cms.FileInPath("RecoEgamma/PhotonIdentification/data/Spring15/effAreaPhotons_cone03_pfChargedHadrons_25ns_NULLcorrection.txt"),
    effAreaNeuHadFile = cms.FileInPath("RecoEgamma/PhotonIdentification/data/Spring15/effAreaPhotons_cone03_pfNeutralHadrons_25ns_90percentBased.txt"),
    effAreaPhoFile = cms.FileInPath("RecoEgamma/PhotonIdentification/data/Spring15/effAreaPhotons_cone03_pfPhotons_25ns_90percentBased.txt"),
    # EGM ID decisions
    phoLooseIdMap = cms.InputTag("egmPhotonIDs:cutBasedPhotonID-Spring15-25ns-V1-standalone-loose"),
    phoMediumIdMap = cms.InputTag("egmPhotonIDs:cutBasedPhotonID-Spring15-25ns-V1-standalone-medium"),
    phoTightIdMap = cms.InputTag("egmPhotonIDs:cutBasedPhotonID-Spring15-25ns-V1-standalone-tight"),
     # gen event info
    genInfo = cms.InputTag("generator", "", "SIM")
    )

#analyzer to print cross section
process.xsec = cms.EDAnalyzer("GenXSecAnalyzer")


#process.p = cms.Path(process.demo)
process.p = cms.Path(process.diphoton)
#process.p = cms.Path(process.egmPhotonIDsequence * process.diphoton * process.xsec)
