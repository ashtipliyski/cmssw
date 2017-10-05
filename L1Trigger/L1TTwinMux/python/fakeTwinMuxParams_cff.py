import FWCore.ParameterSet.Config as cms

RPCLinkMapSource = cms.ESSource('PoolDBESSource'
                                , DBParameters = cms.PSet()
                                , timetype = cms.string('timestamp')
                                , toGet = cms.VPSet(
                                    cms.PSet(
                                        record = cms.string('RPCLBLinkMapRcd')
                                        , tag = cms.string('RPCLBLinkMap_L1T_v1')
                                    )
                                    , cms.PSet(
                                        record = cms.string('RPCDCCLinkMapRcd')
                                        , tag = cms.string('RPCDCCLinkMap_L1T_v1')
                                    )
                                    , cms.PSet(
                                        record = cms.string('RPCTwinMuxLinkMapRcd')
                                        , tag = cms.string('RPCTwinMuxLinkMap_L1T_v1')
                                    )
                                    , cms.PSet(
                                        record = cms.string('RPCCPPFLinkMapRcd')
                                        , tag = cms.string('RPCCPPFLinkMap_L1T_v1')
                                    )
                                    , cms.PSet(
                                        record = cms.string('RPCOMTFLinkMapRcd')
                                        , tag = cms.string('RPCOMTFLinkMap_L1T_v1')
                                    )
                                )
                                , connect = cms.string("frontier://FrontierProd/CMS_CONDITIONS")
)

twinmuxParamsSource = cms.ESSource("EmptyESSource",
    recordName = cms.string('L1TTwinMuxParamsRcd'),
    iovIsRunNotTime = cms.bool(True),
    firstValid = cms.vuint32(1)
)
#ego
bmbtfParamsSource = cms.ESSource(
    "EmptyESSource",
    recordName = cms.string('L1TMuonBarrelParamsRcd'),
    iovIsRunNotTime = cms.bool(True),
    firstValid = cms.vuint32(1)
)

#here
fakeTwinMuxParams = cms.ESProducer('L1TTwinMuxParamsESProducer',
    fwVersion = cms.uint32(1),
    useRpcBxForDtBelowQuality = cms.uint32(4),#correct bx only if dt ts is below
    dphiWindowBxShift         = cms.uint32(9999),
    useOnlyRPC                = cms.bool(False),#use trigger segments (ts)  from rpc hit
    useOnlyDT                 = cms.bool(False),# use ts from dt
    useLowQDT                 = cms.bool(False),
    CorrectDTBxwRPC           = cms.bool(True),#correct bx of dt ts based on rpc
    verbose                   = cms.bool(False),

)
