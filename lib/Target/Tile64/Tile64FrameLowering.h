//===- Tile64FrameLowering.h - Define frame lowering for Tile64 -*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
//                               Tile64 Backend
//
// Author: David Juhasz
// E-mail: juhda@caesar.elte.hu
// Institute: Dept. of Programming Languages and Compilers, ELTE IK, Hungary
//
// The research is supported by the European Union and co-financed by the
// European Social Fund (grant agreement no. TAMOP
// 4.2.1./B-09/1/KMR-2010-0003).
//
//
//===----------------------------------------------------------------------===//

#ifndef TILE64_FRAMEINFO_H
#define Tile64_FRAMEINFO_H

#include "Tile64.h"
#include "llvm/Target/TargetFrameLowering.h"

namespace llvm {

class Tile64FrameLowering : public TargetFrameLowering {
public:
  explicit Tile64FrameLowering()
    : TargetFrameLowering(TargetFrameLowering::StackGrowsDown, 8, 0) {
		//Extra offset for the stored incoming lr is not needed here because LLVM's
		//model works like the incoming sp is the last stack slot used by the
		//caller. (Which is technically true but the callee spills the incoming lr
		//into that slot.)
  }

  /// emitProlog/emitEpilog - These methods insert prolog and epilog code into
  /// the function.
  void emitPrologue(MachineFunction &MF) const;
  void emitEpilogue(MachineFunction &MF, MachineBasicBlock &MBB) const;

	void processFunctionBeforeFrameFinalized(MachineFunction &MF) const;


  //there is a dedicated framepointer (R52).
  bool hasFP(const MachineFunction &MF) const { return true; }
};

} // End llvm namespace

#endif
