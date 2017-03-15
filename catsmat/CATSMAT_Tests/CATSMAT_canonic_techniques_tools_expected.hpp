//
//  CATSMAT_canonic_tools_tests.hpp
//  catsmat
//
//  Created by Jason Stoessel on 10/03/2017.
//
//

#ifndef CATSMAT_canonic_technique_tools_expected_hpp
#define CATSMAT_canonic_technique_tools_expected_hpp

#include <stdio.h>

const string TestScore_Talent_mest_pris_canontype_Expected = "=== Canonic type ===\nNumber of voices: 3\nIOI count: 7 (unit: <RHYTHM_TYPE>minim<\\RHYTHM_TYPE><DOTS>1<\\DOTS><TIME_MOD>1/1<\\TIME_MOD>)\nInterval: per1 / \nMelodically imitative: yes\nStrict: yes\nRetrograde: no\nContrary motion: no\nProportional: no\nStacked: no\nPart: MusicXML Part, Part ID: P1\nPart: MusicXML Part, Part ID: P2\nPart: MusicXML Part, Part ID: P3\n";

const string TestScore_Ockeghem_Prenez_sur_moi_canontype_Expected = "=== Canonic type ===\nNumber of voices: 3\nIOI count: 1 (unit: <RHYTHM_TYPE>semibreve<\\RHYTHM_TYPE><DOTS>1<\\DOTS><TIME_MOD>1/1<\\TIME_MOD>)\nInterval: per4 / \nMelodically imitative: yes\nStrict: yes\nRetrograde: no\nContrary motion: no\nProportional: no\nStacked: yes\nPart: Alto, Part ID: P1\nPart: Tenor, Part ID: P2\nPart: Baritone, Part ID: P3\n";

const string TestScore_Josquin_MAF_Kyrie_canontype_Expected = "This test fails because the file contains several sections of successive canons.";

#endif /* CATSMAT_canonic_tools_expected_hpp */