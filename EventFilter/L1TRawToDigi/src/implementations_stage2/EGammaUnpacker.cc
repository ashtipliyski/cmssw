#include "FWCore/Framework/interface/MakerMacros.h"

#include "EventFilter/L1TRawToDigi/interface/Unpacker.h"

#include "L1Trigger/L1TCalorimeter/interface/CaloTools.h"

#include "L1TObjectCollections.h"

#include "L1TStage2Layer2Constants.h"

namespace l1t {
   namespace stage2 {
      class EGammaUnpacker : public Unpacker {
         public:
            virtual bool unpack(const Block& block, UnpackerCollections *coll) override;
      };
   }
}

// Implementation

namespace l1t {
namespace stage2 {
   bool
   EGammaUnpacker::unpack(const Block& block, UnpackerCollections *coll)
   {

     using namespace l1t::stage2::layer2;

     LogDebug("L1T") << "Block ID  = " << block.header().getID() << " size = " << block.header().getSize();

     int nBX = int(ceil(block.header().getSize() / (double) demux::nOutputFramePerBX)); // 6 link frames per BX

     // Find the central, first and last BXs
     int firstBX = -(ceil((double)nBX/2.)-1);
     int lastBX;
     if (nBX % 2 == 0) {
       lastBX = ceil((double)nBX/2.);
     } else {
       lastBX = ceil((double)nBX/2.)-1;
     }

     auto res_ = static_cast<L1TObjectCollections*>(coll)->getEGammas();
     res_->setBXRange(firstBX, lastBX);

     LogDebug("L1T") << "nBX = " << nBX << " first BX = " << firstBX << " lastBX = " << lastBX;

     // Loop over multiple BX and then number of EG cands filling collection
     for (int bx=firstBX; bx<=lastBX; bx++){

       for (unsigned iEG=0; iEG < demux::nEGPerLink && iEG < block.header().getSize(); iEG++){

	 int iFrame = (bx-firstBX) * demux::nOutputFramePerBX + iEG;
         uint32_t raw_data = block.payload().at(iFrame);

         // skip padding to bring EG candidates up to 12 pre BX
         if (raw_data == 0)
            continue;

         l1t::EGamma eg = l1t::EGamma();
    
         eg.setHwPt(raw_data & 0x1FF);

	 if (eg.hwPt()==0) continue;

	 int abs_eta = (raw_data >> 9) & 0x7F;
         if ((raw_data >> 16) & 0x1) {
           eg.setHwEta(-1*(128-abs_eta));
         } else {
           eg.setHwEta(abs_eta);
         }

         eg.setHwPhi((raw_data >> 17) & 0xFF);
	 eg.setHwIso((raw_data >> 25) & 0x3); 
	 eg.setHwQual((raw_data >> 27) & 0x7); // Assume 3 bits for now? leaves 2 spare bits
       
         LogDebug("L1T") << "EG: eta " << eg.hwEta() << " phi " << eg.hwPhi() << " pT " << eg.hwPt() << " iso " << eg.hwIso() << " qual " << eg.hwQual();

	 eg.setP4( l1t::CaloTools::p4Demux(&eg) );

         res_->push_back(bx,eg);

       }

     }

     return true;
   }
}
}

DEFINE_L1T_UNPACKER(l1t::stage2::EGammaUnpacker);
