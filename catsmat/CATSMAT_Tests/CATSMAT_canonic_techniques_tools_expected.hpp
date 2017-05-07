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

const string TestScore_Talent_mest_pris_canontype_Expected = "**** Canonic techniques for  ****\nNumber of voices: 3\nIOI count: 7 (unit: <RHYTHM_TYPE>minim<\\RHYTHM_TYPE><DOTS>1<\\DOTS><TIME_MOD>1/1<\\TIME_MOD>)\nInterval: per1 / \nMelodically imitative: yes\nStrict: yes\nRetrograde: no\nContrary motion: no\nProportional: no\nStacked: no\nPart: MusicXML Part, Part ID: P1\nPart: MusicXML Part, Part ID: P2\nPart: MusicXML Part, Part ID: P3\n\n";

const string TestScore_Ockeghem_Prenez_sur_moi_canontype_Expected = "**** Canonic techniques for Prenez sur moy ****\nNumber of voices: 3\nIOI count: 1 (unit: <RHYTHM_TYPE>semibreve<\\RHYTHM_TYPE><DOTS>1<\\DOTS><TIME_MOD>1/1<\\TIME_MOD>)\nInterval: per4 / \nMelodically imitative: yes\nStrict: yes\nRetrograde: no\nContrary motion: no\nProportional: no\nStacked: yes\nPart: Alto, Part ID: P1\nPart: Tenor, Part ID: P2\nPart: Baritone, Part ID: P3\n\n";

const string TestScore_Josquin_MAF_Kyrie_canontype_Expected = "Canonic tool doesn't work where a file contains successive canons.";

const string TestScore_Machaut_Ma_fin_est_mon_commencement_Expected = "**** Canonic techniques for Ma fin est mon commencement ****\nNumber of voices: 2\nInterval: per1 / \nMelodically imitative: no\nStrict: yes\nRetrograde: yes\nContrary motion: no\nProportional: no\nStacked: no\nPart: Ca 1, Part ID: P1\nPart: Ca 2, Part ID: P2\n\n";

const string TestScore_Cerreto_CM_canon_Expected = "**** Canonic techniques for Canon in Contrary Motion from Della prattica musica ****\nNumber of voices: 2\nIOI count: 1 (unit: <RHYTHM_TYPE>breve<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD>)\nInterval: maj2 / \nMelodically imitative: no\nStrict: yes\nRetrograde: no\nContrary motion: yes\nProportional: no\nStacked: no\nPart: Tenor, Part ID: P2\nPart: Alto, Part ID: P1\n\n";

const string TestScore_Bononcini_RCM_canon_Expected = "**** Canonic techniques for Canon in Retrograde Contrary Motion from Musico prattico ****\nNumber of voices: 2\nInterval: maj2 \\ \nMelodically imitative: no\nStrict: yes\nRetrograde: yes\nContrary motion: yes\nProportional: no\nStacked: no\nPart: Alto 1, Part ID: P1\nPart: MusicXML Part, Part ID: P2\n\n";

#endif /* CATSMAT_canonic_tools_expected_hpp */
