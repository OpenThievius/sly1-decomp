// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "base_object.h"
#include "placed_object.h"
#include "switched_collider.h"
#include "world.h"
#include "v24a2.h"
#include "shapes.h"
#include "level_entry.h"
#include "threshold_range.h"
#include "g261ef0.h"
#include "render_frame.h"
#include "background_job.h"
#include "group_marker.h"
#include "game_progress.h"
#include "bump_allocator.h"

// Class descriptors (parent, class id, flags, object size, then the class's methods) and the
// method tables of .rodata from 0x217380, defined here until their own files are found.
typedef void (*Fn_Table)();
template <int N> struct ClassDesc_217418 { const void* parent; s32 id; s32 f8; s32 size; Fn_Table methods[N]; };
void func_0011EDA8();
void func_001212D8();
void func_00121338();
void func_00121358();
void func_001214B8();
void func_00121508();
void func_00121568();
void func_00121580();
f32 func_001215A8();
void func_00122550();
void func_001225D0();
void func_00122708();
void func_001227B0();
void func_001227F0();
void func_00122840();
void func_00122858();
f32 func_00122878();
void func_001233C0();
void func_00123408();
void func_00123448();
void func_00123540();
void func_00123578();
void func_00123ED0();
void func_00124050();
void func_001240F8();
void func_00124338();
void func_001243E0();
void func_001245A8();
void func_00124868();
void func_001249A8();
void func_00124A48();
void func_00124FC0();
void func_00125108();
void func_00125138();
void func_00125438();
void func_00125440();
void func_00125C90();
void func_001261C0();
void func_00126270();
void func_00126F78();
void func_00127048();
void func_00127378();
void func_001273F0();
void func_00127478();
void func_001274F8();
void func_00127590();
void func_001276C0();
void func_001289C0();
void func_00128E88();
void func_00128FD0();
void func_00129780();
s32 func_0012B2E8();
void func_0012B6B8();
void func_0012B760();
void func_0012B870();
void func_0012B8C8();
void func_0012C140();
void func_0012C160();
void func_0012D3E0();
void func_0012D3E8();
void func_0012D3F0();
void func_0012F840();
void func_0012F888();
void func_0012F8C8();
void func_0012F9B8();
s32 func_0012FA88();
void func_0012FB68();
void func_00139DE8();
void func_00139E80();
void func_00139EC8();
void func_0013A3A0();
void func_0013A418();
void func_0013A940();
void func_0013AD08();
void func_0013B4C0();
void func_0013B598();
void func_0013B5C8();
void func_0013B610();
void func_0013B708();
void func_0013B778();
void func_0013B9D8();
void func_0013BA70();
void func_0013BBA0();
void func_0013CCF8();
void func_0013CD80();
void func_0013CDE8();
void func_0013CE40();
void func_0013D068();
void func_0013D0B0();
void func_0013D278();
void func_0013DC38();
void func_0013DCA8();
s32 func_0013DD08();
void func_0013DDB8();
void func_0013DDF0();
void func_0013DE38();
void func_0013DEE8();
void func_0013DF68();
void func_0013F0E0();
void func_0013F110();
void func_0013F290();
void func_0013F6C0();
void func_0013FA10();
void func_0013FAE8();
void func_0013FD20();
s32 func_00140028();
void func_001400A8();
void func_00140100();
void func_00140140();
void func_00140200();
void func_00140258();
void func_00141108();
void func_001411A8();
void func_00141210();
void func_00141338();
void func_00141438();
void func_001415D0();
void func_00141690();
s32 func_001417F0();
void func_00143648();
void func_00146100();
void func_00146130();
void func_00146178();
void func_001461A8();
void func_00146340();
void func_001463C0();
void func_00146418();
void func_00146470();
void func_00146518();
s32 func_001473E0();
void func_00147428();
void func_001478F0();
void func_00147AB0();
void func_00147E40();
void func_00147EF8();
void func_00147FB0();
void func_00148298();
void func_00148400();
void func_00148470();
void func_00148510();
void func_00148598();
void func_00148698();
void func_00148718();
void func_00148770();
void func_00148828();
void func_00148888();
void func_00148D90();
void func_00148E40();
void func_00148EF8();
void func_00148FF0();
void func_00149168();
void func_00149190();
void func_0014B550();
void func_0014B588();
void func_0014B5C0();
void func_0014B608();
void func_0014B640();
void func_0014B6A8();
void func_0014BB08();
s32 func_0014BCE8();
void func_0014BD38();
s32 func_0014BDC8();
s32 func_0014BEA8();
s32 func_0014BEF8();
void func_0014BF88();
void func_0014C018();
void func_0014C138();
void func_0014C6E0();
void func_0014C788();
void func_0014CF30();
f32 func_0014DA18();
f32 func_0014DA28();
f32 func_0014DB40();
f32 func_0014DB58();
void func_0014EE40();
void func_0014EE70();
void func_0014EF00();
void func_0014EF40();
void func_0014EF88();
void func_0014EFB8();
void func_0014F020();
void func_0014F058();
void func_0014F740();
void func_0014F770();
void func_0014F850();
void func_0014F920();
void func_0014FA88();
s32 func_0014FBE0();
void func_0014FC38();
void func_001504E0();
void func_00150528();
void func_001506F0();
void func_00150AE8();
void func_001512A8();
void func_00152E28();
void func_00153328();
void func_00154C10();
void func_00154F98();
void func_00155080();
void func_001550E8();
void func_00155270();
void func_00155678();
void func_00155AB0();
void func_001585F8();
void func_001587C0();
void func_001587C8();
void func_00158980();
void func_00158A10();
void func_00158A80();
void func_00158B00();
void func_00158B30();
void func_00158C28();
void func_00158C60();
void func_00158D38();
void func_00158E10();
void func_00158E48();
void func_00158F10();
void func_00158F80();
void func_00159680();
void func_001596E0();
void func_00159890();
void* func_00159A80();
void func_0015A8B8();
void func_0015A918();
void func_0015A960();
void func_0015A9A8();
void func_0015AAE0();
void func_0015AC08();
void func_0015AD80();
void func_0015AE38();
void func_0015AEB0();
void func_0015AF50();
void func_0015B128();
void func_0015B4D0();
s32 func_0015B720();
void func_0015FBB8();
void func_0015FCD8();
void func_0015FF88();
void func_001660A0();
void func_001660E8();
void func_00167D68();
void func_00167E08();
void func_00167EF0();
void func_00167F10();
void func_00169CD8();
void func_00169D20();
void func_00169D58();
void func_00169D90();
void func_00169DD8();
void func_0016A100();
void func_0016A140();
void func_0016A178();
void func_0016A1B0();
void func_0016A1F8();
void func_0016A3A8();
void func_0016A420();
void func_0016A490();
void func_0016A4C8();
void func_0016A500();
s32 func_0016A548();
void func_0016A580();
void func_0016AA18();
void func_0016AED8();
void func_0016C470();
void func_0016C4B8();
void func_0016C4E8();
void func_0016C508();
void func_0016CE00();
void func_0016CE80();
void func_0016CF70();
void func_0016D0C0();
void func_0016D128();
void func_0016DA00();
void func_0016DD10();
void func_0016DD90();
void func_0016DDE8();
void func_0016DF30();
void func_0016DF68();
void func_0016DFE0();
void func_0016F608();
void func_0016F7B0();
void func_0016F810();
void func_001701B0();
void func_00170410();
void func_00170528();
void func_00170660();
s32 func_00170790();
void func_00170820();
void func_00170960();
void func_001721B0();
void func_00172530();
void func_001725E0();
void func_00172898();
void func_00172AE0();
void func_00172B08();
void func_00172B88();
void func_00172CF0();
s32 func_00172EB8();
void func_00172EE0();
void func_00173708();
void func_00173888();
void func_00174808();
s32 func_00177E20();
void func_00177E70();
void func_00177EE0();
void func_00177F98();
void func_00178008();
void func_00178038();
void func_001793C0();
void func_001793F0();
void func_00179590();
void func_00179690();
void func_001796D0();
void func_00179A68();
void func_0017A6D0();
void func_0017A700();
void func_0017A788();
s32 func_0017A9E0();
s32 func_0017AA40();
void func_0017AB58();
s32 func_0017ABD8();
void func_0017ADD0();
void func_0017AE00();
void func_0017AF38();
void func_0017B308();
s32 func_0017B3A8();
void func_0017B5D0();
void func_0017B610();
void func_0017B648();
void func_0017B710();
s32 func_0017B7A8();
void func_0017B998();
void func_0017FD90();
void func_0017FDC8();
void func_0017FE00();
void func_0017FE48();
void func_0017FE90();
void func_0017FEC0();
void func_00180EB0();
void func_00180EE8();
void func_00180F20();
void func_00180F68();
void func_00180F98();
void func_00181078();
void func_00181448();
void func_00181658();
void func_00181780();
void func_00181818();
void func_00181A58();
s32 func_00181A98();
s32 func_00181AE0();
void func_00181AF0();
s32 func_00181BC8();
void func_00181D28();
void func_00181D88();
void func_00182470();
void func_001824D8();
void func_00182548();
void func_00182748();
void func_00182C18();
void func_00182C58();
void func_00182C80();
void func_00182D00();
void func_00182D48();
void func_00182D50();
void func_00182E88();
void func_00182ED0();
void func_00182F78();
void func_001830B0();
void func_001830D8();
void func_00183290();
void func_001832C0();
void func_001832F0();
void func_00183320();
void func_00183350();
void func_001833D0();
void func_00183CC8();
void func_00183D88();
void func_00183E40();
void func_00183E70();
void func_00183EA0();
void func_00185358();
void func_00185498();
void func_00185538();
void func_00187F40();
void func_0018A388();
void func_0018A3B8();
void func_0018A3F0();
void func_0018A628();
s32 func_0018A9A8();
s32 func_0018AAE0();
void func_0018AB88();
s32 func_0018ABF0();
void func_0018ACD0();
void func_0018ACF0();
void func_0018AD88();
void func_0018AE38();
void func_0018B2E8();
void func_0018B340();
void func_0018D8E0();
void func_0018D910();
void func_0018D978();
void func_0018D9B8();
void func_0018DA40();
void func_0018DB20();
s32 func_0018DC88();
void func_0018DDA0();
void func_0018DDD8();
void func_0018DE70();
void func_0018DEE8();
void func_0018E040();
void func_0018F988();
void func_0018F9D8();
void func_0018FEF8();
void func_0018FF28();
void func_0018FFB0();
void func_001900A0();
void func_00190128();
void func_00190258();
s32 func_001903F0();
s32 func_00190450();
s32 func_001904E0();
s32 func_00190570();
s32 func_00190658();
void func_001906F8();
s32 func_00190740();
void func_00190770();
void func_001916D0();
void func_00191F08();
void func_00191F68();
void func_00191FA0();
void func_00191FD8();
void func_00192020();
void func_00192068();
void func_001920E0();
s32 func_00192128();
void func_00192150();
void func_001921A8();
void func_001921E8();
void func_00192230();
void func_001922E8();
void func_00192380();
s32 func_00192410();
s32 func_00192450();
s32 func_00192488();
s32 func_00192490();
void func_001924C8();
void func_001925C0();
void func_00192820();
void func_00192850();
void func_00192A28();
void func_00192A38();
void func_00192B58();
void func_00192C58();
void* func_001930B0();
void func_001963D8();
void func_00196410();
void func_00196810();
void func_00196900();
void func_00196938();
void func_001969C0();
void func_001969F8();
void func_00196B78();
void func_00196EB0();
void func_001974D8();
void func_001974F8();
void func_00197788();
void func_00197A68();
void func_00197A88();
void func_00197F10();
void func_00198090();
void func_001980B0();
s32 func_001982A0();
void func_00198318();
void func_001984B8();
void func_00198530();
void func_00198570();
void func_001986E8();
void func_00198760();
u32 func_00198858();
void func_00198860();
void func_00198920();
void func_00198980();
void func_001989B0();
void func_00198A88();
void func_00198B28();
void func_00198BD8();
void func_00198DA8();
void func_00198E58();
s32 func_00198E98();
void func_00198EF8();
s32 func_00198FB0();
void func_00199000();
void func_00199070();
void func_001990A8();
s32 func_001990E0();
void func_00199138();
void func_00199170();
void func_001991A8();
void func_001991E0();
void func_00199218();
void func_001993F0();
void func_00199428();
void func_001994C8();
void func_00199500();
void func_00199698();
void func_001999D0();
void func_00199C58();
s32 func_00199C78();
void func_00199D08();
void func_0019A148();
void func_0019A1E0();
void func_0019A520();
void func_0019A6A8();
void func_0019AB78();
void func_0019AF00();
void func_0019AF38();
void func_0019AF70();
void func_0019AFA8();
void func_0019AFF0();
void func_0019B038();
void func_0019B0A0();
void func_0019B188();
void func_0019B1E0();
void func_0019B218();
void func_0019B250();
void func_0019B298();
void func_0019B378();
void func_0019BB10();
void func_0019BB90();
void func_0019BC40();
s32 func_0019BE08();
void func_0019C3D0();
void func_0019C408();
void func_0019C440();
void func_0019C470();
void func_0019C728();
void func_0019E0B8();
void func_0019E168();
void func_0019E220();
void func_0019E418();
void func_0019E420();
void func_0019E848();
void func_0019ECE0();
void func_0019ED58();
void func_001A0FE8();
void func_001A1030();
void func_001A11C0();
void func_001A1398();
void func_001A3AE0();
void func_001A3B20();
void func_001A3B58();
void func_001A3C40();
void func_001A3D40();
void func_001A43C8();
void func_001A44E8();
void func_001A4538();
void func_001A45B8();
void func_001A4610();
s32 func_001A4710();
void func_001A4718();
void func_001A48C0();
void func_001A4B30();
void func_001A4C48();
void func_001A4D60();
void func_001A6498();
void func_001A64F8();
void func_001A6540();
void func_001A6588();
void func_001A65C8();
s32 func_001A6DE0();
void func_001A6F88();
void func_001A7008();
void func_001A7050();
void func_001A7098();
void func_001A7128();
void func_001A7230();
void func_001A7290();
s32 func_001A72B0();
void func_001A7520();
void func_001A7550();
void func_001A7588();
void func_001A75D0();
void func_001A7648();
void func_001A7708();
void func_001A7750();
void func_001A7798();
void func_001A7800();
void func_001A7FE8();
void func_001A80E0();
void func_001A84C8();
void func_001A8590();
void func_001A86F8();
void func_001A98F8();
s32 func_001A9928();
void func_001A9960();
void func_001A99B8();
void func_001A99F8();
void func_001A9A40();
void func_001A9A98();
void func_001A9AE8();
void func_001AA1F0();
void func_001AA268();
void func_001AA298();
void func_001AA4F0();
void func_001AA790();
f32 func_001AA898();
f32 func_001AA8A0();
f32 func_001AA8A8();
void func_001AA8C8();
void func_001AA8F0();
void func_001AA958();
void func_001AA998();
s32 func_001AAAC8();
void func_001AAF58();
void func_001AAF88();
void func_001AB058();
void func_001AB198();
f32 func_001AB5D8();
void func_001AC5C0();
void func_001AC638();
void func_001AC700();
void func_001AECB0();
void func_001AECE0();
void func_001AECE8();
void func_001AEFA0();
void func_001AF0A0();
void func_001AF0D0();
void func_001AF108();
void func_001AF3B8();
void func_001AF5C8();
void func_001AF7A8();
void func_001AF820();
void func_001AFBB0();
void func_001B00E8();
void func_001B0120();
void func_001B0160();
void func_001B01B0();
void func_001B04A0();
void func_001B04D0();
void func_001B0578();
void func_001B0838();
s32 func_001B0BD8();
void func_001B0C68();
void func_001B0EA8();
void func_001B0EE0();
void func_001B0F70();
void func_001B0FC0();
void func_001B1158();
void func_001B11A0();
void func_001B1238();
void func_001B1438();
void func_001B15D0();
void func_001B1608();
void func_001B1698();
void func_001B1710();
void func_001B2840();
void func_001B28A8();
void func_001B4AA0();
void func_001B4AD0();
f32 func_001B4B38();
void* func_001B4B48();
void func_001B5CD8();
void func_001B5D28();
void func_001B5F50();
void func_001B61A8();
void func_001B6EC8();
void func_001B7128();
void func_001B7280();
void func_001B7608();
void func_001B7790();
s32 func_001B7818();
s32 func_001B7860();
void func_001B78C0();
void func_001B7920();
void func_001B7968();
void func_001B7A98();
void func_001B7B78();
void func_001B7D00();
void func_001B7F78();
void func_001B8148();
void func_001B8540();
void func_001B8960();
void func_001B89B8();
s32 func_001B8A08();
void func_001B8A48();
void func_001B8B90();
void func_001B9338();
void func_001B93D8();
void func_001B93F8();
void func_001B9680();
void func_001B9690();
void func_001B97E0();
void func_001B9940();
void func_001B99F0();
void func_001B9B50();
void func_001B9C80();
void func_001B9F30();
void func_001BA130();
void func_001BA5B0();
void func_001BAC28();
void func_001BAC30();
void func_001BB210();
s32 func_001BBC30();
void func_001BC088();
s32 func_001BC320();
void func_001BC368();
void func_001BC760();
void func_001BC828();
void func_001BC978();
void func_001C0F30();
void func_001C0FF0();
void func_001C10A8();
void func_001C10D8();
void func_001C1110();
void func_001C1148();
void func_001C3390();
void func_001C33C8();
void func_001C34C8();
void func_001C3928();
void func_001C39A0();
void func_001C3B40();
void func_001C3C00();
void func_001C3C98();
s32 func_001C3D28();
s32 func_001C3D60();
s32 func_001C3E50();
void func_001C3E80();
void func_001C4458();
void func_001C44F0();
void func_001C49C8();
void func_001C4ED0();
s32 func_001C4F00();
void func_001C4F08();
void func_001C4FA0();
void func_001C4FF8();
void func_001C5118();
s32 func_001C5248();
void func_001C5338();
void func_001C5388();
void func_001C53B0();
void func_001C53E0();
void func_001C5438();
void func_001C57C8();
void func_001C5BF0();
void func_001C5DB8();
void func_001C5F18();
void func_001C6028();
void func_001C6F48();
void func_001C7140();
void func_001C7188();
void func_001C71E0();
void func_001C72A0();
s32 func_001C7468();
void func_001C74E8();
void func_001C7520();
void func_001C75B0();
void func_001C7CB8();
s32 func_001C8010();
void func_001C8590();
void func_001C8C08();
void func_001C8E28();
void func_001C9008();
void func_001C91C8();
s32 func_001C96D8();
s32 func_001C9990();
s32 func_001C9A48();
void func_001C9AF8();
void func_001C9CF8();
void func_001C9DE0();
s32 func_001CA460();
s32 func_001CA468();
void func_001CA5E0();
void* func_001CAA08();
void func_001CAC30();
void func_001CACB0();
void func_001CAD98();
s32 func_001CB3C0();
s32 func_001CB3C8();
void func_001CB618();
void func_001CB7A0();
void func_001CD088();
void func_001CDF78();
void func_001D3290();
void func_001D3398();
void func_001D3470();
void func_001D34E0();
void* func_001D3500();
void func_001D35A8();
void func_001D3678();
s32 func_001D4D08();
s32 func_001D54E0();
s32 func_001D65D8();
void func_001D6608();
void func_001D6B18();
s32 func_001D6DA0();
void func_001D6DD8();
void func_001D7018();
void func_001D7040();
void func_001D73A8();
void func_001D7440();
void func_001D7778();
void func_001D9C98();
void func_001D9D78();
void func_001DA170();
void func_001DA310();
void func_001DA320();
void func_001DA6E0();
void func_001DA7E0();
void func_001DAA18();
void func_001DAC20();
void func_001DACB0();
void func_001DAE18();
void func_001DAE48();
void func_001DAE68();
void func_001DAF08();
void func_001DB4C8();
void func_001DCEA0();
void func_001DDCE0();
void func_001DDD18();
void func_001DDE90();
void func_001DE768();
void func_001DE798();
void func_001DE808();
void func_001DE910();
void func_001DEBB8();
void func_001DEBE8();
void func_001DF290();
void func_001DF2C8();
void func_001DF520();
s32 func_001DF5A0();
void func_001DF700();
void func_001DFA10();
void func_001DFA40();
void func_001DFB08();
s32 func_001DFBD0();
void func_001DFD90();
void func_001DFDC8();
void func_001DFE00();
void func_001DFE38();
void func_001E2520();
void func_001E25F8();
void func_001E2648();
void func_001E2758();
void func_001E2940();
void func_001E2988();
void func_001E29A8();
void func_001E5378();
void func_001E5428();
void func_001E55D0();
void func_001E56A0();
void func_001E5750();
void func_001E5CE8();
s32 func_001E5DA8();
void func_001E5E08();
void func_001E5E50();
void* func_001E5E60();
void func_001E88D0();
void func_001E8948();
void func_001E8A50();
s32 func_001E8D58();
s32 func_001E8DB0();
s32 func_001E8DD0();
void func_001E8E08();
void func_001E8E48();
void func_001E8EF8();
void func_001E8FA8();
void func_001E8FE8();
s32 func_001E9038();
void func_001EA118();
void func_001EB460();
void func_001EB518();
void func_001EB598();
void func_001EB608();
void func_001EB748();
s32 func_001EBC88();
s32 func_001EBD08();
void func_001EBD10();
void func_001EBDD0();
void func_001EBEB0();
void func_001EBF40();
void func_001EBFB0();
void func_001EC098();
void func_001EC0B8();
s32 func_001EC0D8();
s32 func_001EC188();
void func_001EC380();
void func_001EC3D8();
void func_001EC478();
void func_001EC570();
void func_001EC828();
void func_001ECBC8();
void func_001ECDF8();
void func_001ECE98();
void func_001ECF10();
void func_001ED168();
void func_001ED198();
void func_001EE900();
void func_001EE930();
void func_001EEC60();
void func_001EECE0();
void func_001EEF90();
void func_001EF3A8();
void func_001EF3D8();
void func_001EF768();
s32 func_001EF808();
void func_001EF838();
void func_001EF868();
void func_001EF8F8();
void func_001EF9C8();
void func_001F0660();
void func_001F0758();
void func_001F0AE0();
void func_001F0EB8();
void func_001F0F70();
void func_001F2758();
void func_001F39F8();
void func_001F3A40();
void func_001F3A90();
void func_001F3AF0();
void func_001F3D80();
void func_001F3EE0();
void func_001F3F80();
void func_001F4500();
void func_001F4660();
void func_001F4AE0();
void func_001F4E18();
void func_001F4E48();
void func_001F4F70();
void func_001F4FD8();
void func_001F5008();
void func_001F51A0();
void func_001F51C8();
int func_001F51E8();
void func_001F5218();
void func_001F5268();
extern const ClassDesc_217418<2> D_00217380;
extern const Fn_Table D_00217410[2];
extern const ClassDesc_217418<28> D_00217418;
extern const ClassDesc_217418<48> D_00217498;
extern const ClassDesc_217418<86> D_00217568;
extern const ClassDesc_217418<28> D_00217740;
extern const ClassDesc_217418<28> D_002177C0;
extern const ClassDesc_217418<28> D_00217840;
extern const ClassDesc_217418<28> D_002178C0;
extern const ClassDesc_217418<28> D_00217940;
extern const ClassDesc_217418<48> D_002179C0;
extern const ClassDesc_217418<48> D_00217A90;
extern const ClassDesc_217418<48> D_00217B60;
extern const ClassDesc_217418<124> D_00217C30;
extern const Fn_Table D_00218330[20];
extern const ClassDesc_217418<28> D_00218650;
extern const ClassDesc_217418<72> D_00218770;
extern const ClassDesc_217418<48> D_002188A0;
extern const ClassDesc_217418<74> D_00218970;
extern const ClassDesc_217418<72> D_00218AA8;
extern const ClassDesc_217418<74> D_00218BD8;
extern const ClassDesc_217418<74> D_00218D10;
extern const ClassDesc_217418<74> D_00218E48;
extern const ClassDesc_217418<72> D_00218F80;
extern const ClassDesc_217418<72> D_002190B0;
extern const ClassDesc_217418<28> D_002191E0;
extern const ClassDesc_217418<48> D_00219260;
extern const ClassDesc_217418<72> D_00219330;
extern const ClassDesc_217418<28> D_00219460;
extern const ClassDesc_217418<28> D_002194E0;
extern const Fn_Table D_00219560[10];
extern const Fn_Table D_00219588[10];
extern const ClassDesc_217418<28> D_00219738;
extern const ClassDesc_217418<28> D_002197E8;
extern const ClassDesc_217418<28> D_00219868;
extern const ClassDesc_217418<72> D_002198F0;
extern const ClassDesc_217418<48> D_00219A20;
extern const ClassDesc_217418<72> D_00219AF0;
extern const Fn_Table D_00219DE0[8];
extern const ClassDesc_217418<48> D_00219F80;
extern const ClassDesc_217418<48> D_0021A050;
extern const ClassDesc_217418<28> D_0021A120;
extern const ClassDesc_217418<28> D_0021A1A0;
extern const ClassDesc_217418<28> D_0021A220;
extern const ClassDesc_217418<28> D_0021A2A0;
extern const ClassDesc_217418<48> D_0021A320;
extern const ClassDesc_217418<48> D_0021A490;
extern const ClassDesc_217418<28> D_0021A560;
extern const ClassDesc_217418<28> D_0021A5E0;
extern const ClassDesc_217418<72> D_0021A660;
extern const Fn_Table D_0021A790[10];
extern const ClassDesc_217418<28> D_0021A7B8;
extern const ClassDesc_217418<88> D_0021A838;
extern const Fn_Table D_0021A9A8[10];
extern const ClassDesc_217418<74> D_0021A9D0;
extern const ClassDesc_217418<72> D_0021AB08;
extern const ClassDesc_217418<78> D_0021AC38;
extern const ClassDesc_217418<78> D_0021AD80;
extern const ClassDesc_217418<78> D_0021AEC8;
extern const ClassDesc_217418<78> D_0021B010;
extern const ClassDesc_217418<28> D_0021B158;
extern const ClassDesc_217418<28> D_0021B1D8;
extern const ClassDesc_217418<28> D_0021B258;
extern const ClassDesc_217418<72> D_0021B2D8;
extern const ClassDesc_217418<48> D_0021B408;
extern const ClassDesc_217418<72> D_0021B4D8;
extern const ClassDesc_217418<28> D_0021B608;
extern const ClassDesc_217418<88> D_0021B688;
extern const ClassDesc_217418<28> D_0021B7F8;
extern const ClassDesc_217418<72> D_0021B878;
extern const ClassDesc_217418<72> D_0021B9A8;
extern const ClassDesc_217418<28> D_0021BAD8;
extern const ClassDesc_217418<100> D_0021BB58;
extern const ClassDesc_217418<100> D_0021BCF8;
extern const ClassDesc_217418<100> D_0021BE98;
extern const ClassDesc_217418<72> D_0021C038;
extern const ClassDesc_217418<72> D_0021C168;
extern const ClassDesc_217418<28> D_0021C298;
extern const ClassDesc_217418<72> D_0021C318;
extern const ClassDesc_217418<28> D_0021C448;
extern const ClassDesc_217418<48> D_0021C4C8;
extern const ClassDesc_217418<72> D_0021C598;
extern const ClassDesc_217418<48> D_0021C6C8;
extern const ClassDesc_217418<48> D_0021C798;
extern const ClassDesc_217418<48> D_0021C868;
extern const ClassDesc_217418<48> D_0021C938;
extern const ClassDesc_217418<48> D_0021CA08;
extern const ClassDesc_217418<48> D_0021CAD8;
extern const ClassDesc_217418<48> D_0021CBA8;
extern const ClassDesc_217418<76> D_0021CC78;
extern const ClassDesc_217418<76> D_0021CDB8;
extern const ClassDesc_217418<76> D_0021CEF8;
extern const ClassDesc_217418<48> D_0021D038;
extern const ClassDesc_217418<48> D_0021D108;
extern const ClassDesc_217418<84> D_0021D1D8;
extern const ClassDesc_217418<28> D_0021D338;
extern const ClassDesc_217418<72> D_0021D3B8;
extern const ClassDesc_217418<48> D_0021D4E8;
extern const ClassDesc_217418<84> D_0021D5B8;
extern const ClassDesc_217418<72> D_0021D718;
extern const ClassDesc_217418<72> D_0021D848;
extern const ClassDesc_217418<72> D_0021D978;
extern const ClassDesc_217418<72> D_0021DAA8;
extern const ClassDesc_217418<72> D_0021DBD8;
extern const ClassDesc_217418<74> D_0021DD08;
extern const ClassDesc_217418<48> D_0021DE40;
extern const ClassDesc_217418<74> D_0021DF10;
extern const ClassDesc_217418<74> D_0021E048;
extern const ClassDesc_217418<74> D_0021E180;
extern const ClassDesc_217418<36> D_0021E2B8;
extern const Fn_Table D_0021E438[8];
extern const ClassDesc_217418<72> D_0021E458;
extern const ClassDesc_217418<48> D_0021E588;
extern const ClassDesc_217418<48> D_0021E658;
extern const ClassDesc_217418<100> D_0021E728;
extern const ClassDesc_217418<100> D_0021E8C8;
extern const ClassDesc_217418<100> D_0021EA68;
extern const ClassDesc_217418<84> D_0021EC08;
extern const ClassDesc_217418<100> D_0021ED68;
extern const ClassDesc_217418<28> D_0021EF08;
extern const ClassDesc_217418<48> D_0021EF88;
extern const ClassDesc_217418<72> D_0021F058;
extern const ClassDesc_217418<72> D_0021F188;
extern const ClassDesc_217418<28> D_0021F2B8;
extern const ClassDesc_217418<28> D_0021F338;
extern const ClassDesc_217418<28> D_0021F3B8;
extern const ClassDesc_217418<28> D_0021F438;
extern const ClassDesc_217418<88> D_0021F4B8;
extern const ClassDesc_217418<84> D_0021F628;
extern const ClassDesc_217418<100> D_0021F788;
extern const ClassDesc_217418<84> D_0021F928;
extern const ClassDesc_217418<100> D_0021FA88;
extern const ClassDesc_217418<72> D_0021FC28;
extern const ClassDesc_217418<72> D_0021FD58;
extern const ClassDesc_217418<100> D_0021FE88;
extern const ClassDesc_217418<100> D_00220028;
extern const ClassDesc_217418<100> D_002201C8;
extern const ClassDesc_217418<48> D_00220368;
extern const ClassDesc_217418<84> D_00220438;
extern const ClassDesc_217418<84> D_00220598;
extern const ClassDesc_217418<72> D_002206F8;
extern const ClassDesc_217418<72> D_00220828;
extern const ClassDesc_217418<74> D_00220958;
extern const ClassDesc_217418<84> D_00220A90;
extern const ClassDesc_217418<28> D_00220C40;
extern const ClassDesc_217418<84> D_00220CC0;
extern const ClassDesc_217418<72> D_00220E20;
extern const ClassDesc_217418<48> D_00220F50;
extern const ClassDesc_217418<48> D_00221020;
extern const ClassDesc_217418<48> D_00221140;
extern const ClassDesc_217418<48> D_00221210;
extern const ClassDesc_217418<48> D_002213D0;
extern const ClassDesc_217418<28> D_002214A0;
extern const ClassDesc_217418<28> D_00221520;
extern const ClassDesc_217418<2> D_00217380 = { 0x0, 0x0, 0x0, 0x0, {
    0, 0,
} };
extern const Fn_Table D_00217410[2] = {
    0, 0,
};
extern const ClassDesc_217418<28> D_00217418 = { (const void*)(const u8*)&D_00217410, 0x1, 0x0, 0x34, {
    (Fn_Table)func_00182C18, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00182D00, (Fn_Table)func_00182E88, (Fn_Table)func_00182D48, (Fn_Table)func_00182ED0,
    (Fn_Table)func_001830B0, (Fn_Table)func_001830D8, (Fn_Table)func_001833D0, 0,
    0, 0, (Fn_Table)func_00183350, 0,
    (Fn_Table)func_00182C58, 0, 0, 0,
    0, (Fn_Table)func_00182F78, 0, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, 0,
} };
extern const ClassDesc_217418<48> D_00217498 = { (const void*)(const u8*)&D_00217418, 0x2, 0x1, 0x2D0, {
    (Fn_Table)func_00123ED0, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001240F8, (Fn_Table)func_001243E0,
    (Fn_Table)func_00126F78, (Fn_Table)func_00127048, (Fn_Table)func_001289C0, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_00183350, (Fn_Table)func_001249A8,
    (Fn_Table)func_00124A48, (Fn_Table)func_00124FC0, (Fn_Table)func_00125108, (Fn_Table)func_00125138,
    (Fn_Table)func_0015FBB8, (Fn_Table)func_001245A8, (Fn_Table)func_00124868, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_00125440,
    (Fn_Table)func_00125438, (Fn_Table)func_001273F0, (Fn_Table)func_00127478, (Fn_Table)func_001276C0,
    (Fn_Table)func_001274F8, (Fn_Table)func_00127590, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001261C0, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_0012B2E8, 0, 0,
} };
extern const ClassDesc_217418<86> D_00217568 = { (const void*)(const u8*)&D_00217498, 0x3, 0x3, 0x550, {
    (Fn_Table)func_001B7968, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001B7A98, (Fn_Table)func_001B7B78,
    (Fn_Table)func_00126F78, (Fn_Table)func_001BA130, (Fn_Table)func_001BAC30, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_00124A48, (Fn_Table)func_001B93F8, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001B9338, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001B93D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001BC320, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_001B8A08, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_001B9F30, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
    0, 0, 0, 0,
    0, (Fn_Table)func_0014DA18, (Fn_Table)func_0014DA28, (Fn_Table)func_0014DB40,
    (Fn_Table)func_0014DB58, 0, 0, 0,
    0, 0,
} };
extern const ClassDesc_217418<28> D_00217740 = { (const void*)(const u8*)&D_00217418, 0x6E, 0x0, 0x38, {
    (Fn_Table)func_00182C18, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00182D00, (Fn_Table)func_00182E88, (Fn_Table)func_00182D48, (Fn_Table)func_00182ED0,
    (Fn_Table)func_001830B0, (Fn_Table)func_001830D8, (Fn_Table)func_001B2840, 0,
    0, 0, (Fn_Table)func_00183350, 0,
    (Fn_Table)func_00182C58, 0, 0, 0,
    0, (Fn_Table)func_001B28A8, 0, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, 0,
} };
extern const ClassDesc_217418<28> D_002177C0 = { (const void*)(const u8*)&D_00217418, 0x7E, 0x0, 0x50, {
    (Fn_Table)func_00182C18, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00182D00, (Fn_Table)func_00182E88, (Fn_Table)func_00182D48, (Fn_Table)func_00182ED0,
    (Fn_Table)func_001830B0, (Fn_Table)func_001830D8, (Fn_Table)func_00192068, 0,
    0, 0, (Fn_Table)func_00183350, 0,
    (Fn_Table)func_00182C58, 0, 0, 0,
    0, (Fn_Table)func_001920E0, (Fn_Table)func_00192128, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, 0,
} };
extern const ClassDesc_217418<28> D_00217840 = { (const void*)(const u8*)&D_002177C0, 0x82, 0x0, 0x60, {
    (Fn_Table)func_00182C18, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00182D00, (Fn_Table)func_00182E88, (Fn_Table)func_00182D48, (Fn_Table)func_00182ED0,
    (Fn_Table)func_001830B0, (Fn_Table)func_001830D8, (Fn_Table)func_00192150, 0,
    0, 0, (Fn_Table)func_00183350, 0,
    (Fn_Table)func_00182C58, 0, 0, 0,
    0, (Fn_Table)func_001920E0, (Fn_Table)func_00192128, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, 0,
} };
extern const ClassDesc_217418<28> D_002178C0 = { (const void*)(const u8*)&D_00217418, 0x73, 0x0, 0x80, {
    (Fn_Table)func_001F39F8, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00182D00, (Fn_Table)func_00182E88, (Fn_Table)func_00182D48, (Fn_Table)func_00182ED0,
    (Fn_Table)func_001830B0, (Fn_Table)func_001830D8, (Fn_Table)func_001F3A40, 0,
    0, 0, (Fn_Table)func_00183350, 0,
    (Fn_Table)func_00182C58, 0, 0, 0,
    0, (Fn_Table)func_001F3A90, (Fn_Table)func_001F3AF0, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, 0,
} };
extern const ClassDesc_217418<28> D_00217940 = { (const void*)(const u8*)&D_002178C0, 0x74, 0x0, 0x100, {
    (Fn_Table)func_001F39F8, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00182D00, (Fn_Table)func_00182E88, (Fn_Table)func_00182D48, (Fn_Table)func_00182ED0,
    (Fn_Table)func_001830B0, (Fn_Table)func_001F3EE0, (Fn_Table)func_001F3D80, 0,
    0, 0, (Fn_Table)func_00183350, 0,
    (Fn_Table)func_001F3F80, 0, 0, 0,
    0, (Fn_Table)func_001F3A90, (Fn_Table)func_001F3AF0, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, 0,
} };
extern const ClassDesc_217418<48> D_002179C0 = { (const void*)(const u8*)&D_00217498, 0x7D, 0x1, 0x330, {
    (Fn_Table)func_00123ED0, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001240F8, (Fn_Table)func_001243E0,
    (Fn_Table)func_00126F78, (Fn_Table)func_00127048, (Fn_Table)func_001F4500, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_00183350, (Fn_Table)func_001249A8,
    (Fn_Table)func_001F4660, (Fn_Table)func_001F4AE0, (Fn_Table)func_00125108, (Fn_Table)func_00125138,
    (Fn_Table)func_0015FBB8, (Fn_Table)func_001245A8, (Fn_Table)func_00124868, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_00125440,
    (Fn_Table)func_00125438, (Fn_Table)func_001273F0, (Fn_Table)func_00127478, (Fn_Table)func_001276C0,
    (Fn_Table)func_001274F8, (Fn_Table)func_00127590, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001261C0, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_0012B2E8, 0, 0,
} };
extern const ClassDesc_217418<48> D_00217A90 = { (const void*)(const u8*)&D_00217498, 0x4E, 0x1, 0x320, {
    (Fn_Table)func_001F4E18, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001240F8, (Fn_Table)func_001243E0,
    (Fn_Table)func_00126F78, (Fn_Table)func_00127048, (Fn_Table)func_001289C0, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_00183350, (Fn_Table)func_001249A8,
    (Fn_Table)func_001F4E48, (Fn_Table)func_00124FC0, (Fn_Table)func_00125108, (Fn_Table)func_00125138,
    (Fn_Table)func_0015FBB8, (Fn_Table)func_001245A8, (Fn_Table)func_00124868, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_00125440,
    (Fn_Table)func_00125438, (Fn_Table)func_001273F0, (Fn_Table)func_00127478, (Fn_Table)func_001276C0,
    (Fn_Table)func_001274F8, (Fn_Table)func_00127590, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001261C0, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_0012B2E8, 0, 0,
} };
extern const ClassDesc_217418<48> D_00217B60 = { (const void*)(const u8*)&D_00217498, 0x51, 0x1, 0x620, {
    (Fn_Table)func_00183CC8, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_00183E40, (Fn_Table)func_00183E70,
    (Fn_Table)func_00126F78, (Fn_Table)func_00183EA0, (Fn_Table)func_001289C0, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_00183350, (Fn_Table)func_001249A8,
    (Fn_Table)func_00124A48, (Fn_Table)func_00124FC0, (Fn_Table)func_00125108, (Fn_Table)func_00183D88,
    (Fn_Table)func_0015FBB8, (Fn_Table)func_001245A8, (Fn_Table)func_00124868, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_00125440,
    (Fn_Table)func_00125438, (Fn_Table)func_001273F0, (Fn_Table)func_00127478, (Fn_Table)func_001276C0,
    (Fn_Table)func_001274F8, (Fn_Table)func_00127590, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001261C0, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_0012B2E8, 0, 0,
} };
extern const ClassDesc_217418<124> D_00217C30 = { (const void*)(const u8*)&D_00217568, 0x5, 0xB, 0x610, {
    (Fn_Table)func_001921A8, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_00192820, (Fn_Table)func_00192850,
    (Fn_Table)func_00126F78, (Fn_Table)func_001921E8, (Fn_Table)func_001BAC30, 0,
    0, (Fn_Table)func_00192230, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_00124A48, (Fn_Table)func_00192B58, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001B9338, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001B93D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001BC320, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_001B8A08, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_00192380, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
    (Fn_Table)func_001922E8, 0, (Fn_Table)func_00192410, (Fn_Table)func_00192450,
    (Fn_Table)func_00192488, (Fn_Table)func_00192490, (Fn_Table)func_001924C8, (Fn_Table)func_001925C0,
    (Fn_Table)func_00192C58, (Fn_Table)func_00192A28, (Fn_Table)func_00192A38, (Fn_Table)func_001930B0,
    (Fn_Table)func_001AA1F0, (Fn_Table)func_001AA268, (Fn_Table)func_001AA298, 0,
    0, (Fn_Table)func_001AA8C8, 0, 0,
    (Fn_Table)func_001AA4F0, (Fn_Table)func_001AA790, 0, (Fn_Table)func_001AA898,
    (Fn_Table)func_001AA8A0, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958,
    (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0,
    (Fn_Table)func_001AA1F0, (Fn_Table)func_001AAF88, (Fn_Table)func_001AB058, 0,
    0, (Fn_Table)func_001AA8C8, 0, 0,
    (Fn_Table)func_001AA4F0, (Fn_Table)func_001AB198, 0, (Fn_Table)func_001AA898,
    (Fn_Table)func_001AB5D8, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958,
    (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0,
} };
extern const Fn_Table D_00218330[20] = {
    (Fn_Table)func_001AA1F0, (Fn_Table)func_001AC5C0, (Fn_Table)func_001AA298, 0,
    0, (Fn_Table)func_001AA8C8, 0, 0,
    (Fn_Table)func_001AC638, (Fn_Table)func_001AC700, 0, (Fn_Table)func_001AA898,
    (Fn_Table)func_001AA8A0, (Fn_Table)func_001AA8A8, (Fn_Table)func_001AA8F0, (Fn_Table)func_001AA958,
    (Fn_Table)func_001AA998, (Fn_Table)func_001AAF58, (Fn_Table)func_001AAAC8, 0,
};
extern const ClassDesc_217418<28> D_00218650 = { (const void*)(const u8*)&D_00217418, 0x8E, 0x0, 0xA0, {
    (Fn_Table)func_0017FE90, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00182D00, (Fn_Table)func_00182E88, (Fn_Table)func_00182D48, (Fn_Table)func_00182ED0,
    (Fn_Table)func_001830B0, (Fn_Table)func_001830D8, (Fn_Table)func_0017FEC0, 0,
    0, 0, (Fn_Table)func_00183350, 0,
    (Fn_Table)func_00182C58, 0, 0, 0,
    0, (Fn_Table)func_00182F78, 0, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, 0,
} };
extern const ClassDesc_217418<72> D_00218770 = { (const void*)(const u8*)&D_00217568, 0x1F, 0x83, 0x6B0, {
    (Fn_Table)func_001EEC60, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001B7A98, (Fn_Table)func_001B7B78,
    (Fn_Table)func_00126F78, (Fn_Table)func_001BA130, (Fn_Table)func_001BAC30, 0,
    0, (Fn_Table)func_001EF3D8, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_001EECE0, (Fn_Table)func_001EEF90, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001B9338, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001B93D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001BC320, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001EF768, (Fn_Table)func_001EF3A8,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_001B8A08, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_001B9F30, (Fn_Table)func_001BA5B0, (Fn_Table)func_001EF808,
} };
extern const ClassDesc_217418<48> D_002188A0 = { (const void*)(const u8*)&D_00217498, 0x63, 0x1, 0x470, {
    (Fn_Table)func_001E2520, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001240F8, (Fn_Table)func_001E25F8,
    (Fn_Table)func_00126F78, (Fn_Table)func_00127048, (Fn_Table)func_001E2648, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_00183350, (Fn_Table)func_001249A8,
    (Fn_Table)func_001E2758, (Fn_Table)func_001E2940, (Fn_Table)func_00125108, (Fn_Table)func_00125138,
    (Fn_Table)func_001E29A8, (Fn_Table)func_001245A8, (Fn_Table)func_00124868, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_00125440,
    (Fn_Table)func_00125438, (Fn_Table)func_001273F0, (Fn_Table)func_00127478, (Fn_Table)func_001276C0,
    (Fn_Table)func_001274F8, (Fn_Table)func_00127590, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001E2988, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_0012B2E8, 0, 0,
} };
extern const ClassDesc_217418<74> D_00218970 = { (const void*)(const u8*)&D_00217568, 0x20, 0x3, 0x6C0, {
    (Fn_Table)func_0013CCF8, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001B7A98, (Fn_Table)func_001B7B78,
    (Fn_Table)func_00126F78, (Fn_Table)func_0013CDE8, (Fn_Table)func_0013CD80, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_0013CE40, (Fn_Table)func_0013D068, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001B9338, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001B93D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_0013D0B0, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_001B8A08, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_001B9F30, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
    (Fn_Table)func_0013D278, 0,
} };
extern const ClassDesc_217418<72> D_00218AA8 = { (const void*)(const u8*)&D_00217568, 0x27, 0x3, 0x570, {
    (Fn_Table)func_001B7968, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001B7A98, (Fn_Table)func_001B7B78,
    (Fn_Table)func_00126F78, (Fn_Table)func_001BA130, (Fn_Table)func_001BAC30, 0,
    0, (Fn_Table)func_0013DCA8, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_00124A48, (Fn_Table)func_0013DC38, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001B9338, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001B93D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001BC320, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_0013DD08, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_001B9F30, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
} };
extern const ClassDesc_217418<74> D_00218BD8 = { (const void*)(const u8*)&D_00218970, 0x21, 0x13, 0x6C0, {
    (Fn_Table)func_0013DDB8, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001B7A98, (Fn_Table)func_001B7B78,
    (Fn_Table)func_00126F78, (Fn_Table)func_0013CDE8, (Fn_Table)func_0013CD80, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_0013CE40, (Fn_Table)func_0013D068, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001B9338, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001B93D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_0013D0B0, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_001B8A08, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_001B9F30, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
    (Fn_Table)func_0013D278, 0,
} };
extern const ClassDesc_217418<74> D_00218D10 = { (const void*)(const u8*)&D_00218970, 0x25, 0x3, 0x6D0, {
    (Fn_Table)func_0013DDF0, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001B7A98, (Fn_Table)func_001B7B78,
    (Fn_Table)func_00126F78, (Fn_Table)func_0013CDE8, (Fn_Table)func_0013CD80, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_0013CE40, (Fn_Table)func_0013D068, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001B9338, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001B93D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_0013D0B0, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_001B8A08, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    (Fn_Table)func_0013DE38, 0, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_001B9F30, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
    (Fn_Table)func_0013D278, 0,
} };
extern const ClassDesc_217418<74> D_00218E48 = { (const void*)(const u8*)&D_00218D10, 0x26, 0x3, 0x6E0, {
    (Fn_Table)func_0013DDF0, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001B7A98, (Fn_Table)func_001B7B78,
    (Fn_Table)func_00126F78, (Fn_Table)func_0013CDE8, (Fn_Table)func_0013CD80, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_0013CE40, (Fn_Table)func_0013DF68, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001B9338, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001B93D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_0013D0B0, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_001B8A08, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    (Fn_Table)func_0013DEE8, 0, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_001B9F30, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
    (Fn_Table)func_0013D278, 0,
} };
extern const ClassDesc_217418<72> D_00218F80 = { (const void*)(const u8*)&D_00217568, 0x29, 0x3, 0x7A0, {
    (Fn_Table)func_001400A8, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001B7A98, (Fn_Table)func_001B7B78,
    (Fn_Table)func_00126F78, (Fn_Table)func_00140200, (Fn_Table)func_00140100, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_00140140, (Fn_Table)func_00140258, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001B9338, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001B93D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001BC320, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_001B8A08, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_001B9F30, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
} };
extern const ClassDesc_217418<72> D_002190B0 = { (const void*)(const u8*)&D_00217568, 0x28, 0x3, 0x890, {
    (Fn_Table)func_0013F0E0, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001B7A98, (Fn_Table)func_001B7B78,
    (Fn_Table)func_00126F78, (Fn_Table)func_0013F6C0, (Fn_Table)func_0013F110, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_0013F290, (Fn_Table)func_0013FD20, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_0013FA10, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001B93D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_00140028, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_001B8A08, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    0, 0, 0, 0,
    (Fn_Table)func_0013FAE8, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_001B9F30, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
} };
extern const ClassDesc_217418<28> D_002191E0 = { (const void*)(const u8*)&D_00217418, 0x87, 0x0, 0x68, {
    (Fn_Table)func_00182C18, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00182D00, (Fn_Table)func_00182E88, (Fn_Table)func_00182D48, (Fn_Table)func_00182ED0,
    (Fn_Table)func_001830B0, (Fn_Table)func_001830D8, (Fn_Table)func_001833D0, 0,
    0, 0, (Fn_Table)func_00183350, 0,
    (Fn_Table)func_0015FF88, 0, 0, 0,
    0, (Fn_Table)func_00182F78, 0, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, 0,
} };
extern const ClassDesc_217418<48> D_00219260 = { (const void*)(const u8*)&D_00217498, 0x4F, 0x1, 0x2D0, {
    (Fn_Table)func_00123ED0, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001240F8, (Fn_Table)func_001243E0,
    (Fn_Table)func_00126F78, (Fn_Table)func_00127048, (Fn_Table)func_001289C0, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_00183350, (Fn_Table)func_001249A8,
    (Fn_Table)func_00124A48, (Fn_Table)func_00124FC0, (Fn_Table)func_00125108, (Fn_Table)func_00125138,
    (Fn_Table)func_0015FBB8, (Fn_Table)func_001245A8, (Fn_Table)func_00124868, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_00125440,
    (Fn_Table)func_00125438, (Fn_Table)func_001273F0, (Fn_Table)func_00127478, (Fn_Table)func_001276C0,
    (Fn_Table)func_001274F8, (Fn_Table)func_00127590, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001261C0, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_0012B2E8, 0, 0,
} };
extern const ClassDesc_217418<72> D_00219330 = { (const void*)(const u8*)&D_00217568, 0x2B, 0x3, 0x550, {
    (Fn_Table)func_001B7968, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001B7A98, (Fn_Table)func_001B7B78,
    (Fn_Table)func_00126F78, (Fn_Table)func_001BA130, (Fn_Table)func_001BAC30, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_00124A48, (Fn_Table)func_001B93F8, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001B9338, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001B93D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001BC320, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_001B8A08, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_001B9F30, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
} };
extern const ClassDesc_217418<28> D_00219460 = { (const void*)(const u8*)&D_00217418, 0x86, 0x0, 0x44, {
    (Fn_Table)func_001EE900, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00182D00, (Fn_Table)func_00182E88, (Fn_Table)func_00182D48, (Fn_Table)func_00182ED0,
    (Fn_Table)func_001830B0, (Fn_Table)func_001830D8, (Fn_Table)func_001EE930, 0,
    0, 0, (Fn_Table)func_00183350, 0,
    (Fn_Table)func_00182C58, 0, 0, 0,
    0, (Fn_Table)func_00182F78, 0, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, 0,
} };
extern const ClassDesc_217418<28> D_002194E0 = { (const void*)(const u8*)&D_00217418, 0x85, 0x0, 0x34, {
    (Fn_Table)func_00182C18, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00182D00, (Fn_Table)func_00182E88, (Fn_Table)func_00182D48, (Fn_Table)func_00182ED0,
    (Fn_Table)func_001830B0, (Fn_Table)func_001830D8, (Fn_Table)func_001833D0, 0,
    0, 0, (Fn_Table)func_00183350, 0,
    (Fn_Table)func_00182C58, 0, 0, 0,
    0, (Fn_Table)func_00182F78, 0, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, 0,
} };
extern const Fn_Table D_00219560[10] = {
    (Fn_Table)func_00121338, (Fn_Table)func_001212D8, (Fn_Table)func_00121358, 0,
    (Fn_Table)func_001214B8, (Fn_Table)func_00121508, (Fn_Table)func_00121568, (Fn_Table)func_00121580,
    (Fn_Table)func_001215A8, 0,
};
extern const Fn_Table D_00219588[10] = {
    (Fn_Table)func_00122708, (Fn_Table)func_001212D8, (Fn_Table)func_00121358, 0,
    (Fn_Table)func_001227B0, (Fn_Table)func_001227F0, (Fn_Table)func_00122840, (Fn_Table)func_00122858,
    (Fn_Table)func_00122878, 0,
};
extern const ClassDesc_217418<28> D_00219738 = { (const void*)(const u8*)&D_00217418, 0x83, 0x40, 0xB0, {
    (Fn_Table)func_0012B870, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00182D00, (Fn_Table)func_00182E88, (Fn_Table)func_00182D48, (Fn_Table)func_00182ED0,
    (Fn_Table)func_001830B0, (Fn_Table)func_0012C140, (Fn_Table)func_0012B8C8, 0,
    0, 0, (Fn_Table)func_00183350, 0,
    (Fn_Table)func_0012C160, 0, 0, 0,
    0, (Fn_Table)func_00182F78, 0, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, 0,
} };
extern const ClassDesc_217418<28> D_002197E8 = { (const void*)(const u8*)&D_00219738, 0x84, 0x40, 0xD0, {
    (Fn_Table)func_0012B870, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00182D00, (Fn_Table)func_00182E88, (Fn_Table)func_00182D48, (Fn_Table)func_00182ED0,
    (Fn_Table)func_001830B0, (Fn_Table)func_0012D3F0, (Fn_Table)func_0012D3E0, 0,
    0, 0, (Fn_Table)func_00183350, 0,
    (Fn_Table)func_0012D3E8, 0, 0, 0,
    0, (Fn_Table)func_00182F78, 0, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, 0,
} };
extern const ClassDesc_217418<28> D_00219868 = { (const void*)(const u8*)&D_00217418, 0x88, 0x0, 0x54, {
    (Fn_Table)func_00182C18, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00182D00, (Fn_Table)func_00182E88, (Fn_Table)func_00182D48, (Fn_Table)func_00182ED0,
    (Fn_Table)func_001830B0, (Fn_Table)func_001830D8, (Fn_Table)func_001B5F50, 0,
    0, 0, (Fn_Table)func_00183350, 0,
    (Fn_Table)func_001B61A8, 0, 0, 0,
    0, (Fn_Table)func_00182F78, 0, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, 0,
} };
extern const ClassDesc_217418<72> D_002198F0 = { (const void*)(const u8*)&D_00217568, 0x35, 0x3, 0x550, {
    (Fn_Table)func_001B7968, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001B7A98, (Fn_Table)func_001B7B78,
    (Fn_Table)func_00126F78, (Fn_Table)func_001BA130, (Fn_Table)func_001BAC30, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_00124A48, (Fn_Table)func_001B93F8, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001B9338, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_0016C4E8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001BC320, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_001B8A08, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_001B9F30, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
} };
extern const ClassDesc_217418<48> D_00219A20 = { (const void*)(const u8*)&D_00217498, 0x52, 0x1, 0x2D0, {
    (Fn_Table)func_00123ED0, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001240F8, (Fn_Table)func_001243E0,
    (Fn_Table)func_00126F78, (Fn_Table)func_00127048, (Fn_Table)func_001289C0, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_00183350, (Fn_Table)func_001249A8,
    (Fn_Table)func_00124A48, (Fn_Table)func_00124FC0, (Fn_Table)func_00125108, (Fn_Table)func_00125138,
    (Fn_Table)func_0015FBB8, (Fn_Table)func_001245A8, (Fn_Table)func_00124868, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_00125440,
    (Fn_Table)func_00125438, (Fn_Table)func_001273F0, (Fn_Table)func_00127478, (Fn_Table)func_001276C0,
    (Fn_Table)func_001274F8, (Fn_Table)func_00127590, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_0016C508, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_0012B2E8, 0, 0,
} };
extern const ClassDesc_217418<72> D_00219AF0 = { (const void*)(const u8*)&D_00217568, 0x1E, 0x3, 0x570, {
    (Fn_Table)func_0019E0B8, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001B7A98, (Fn_Table)func_0019E168,
    (Fn_Table)func_00126F78, (Fn_Table)func_001BA130, (Fn_Table)func_001BAC30, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_00124A48, (Fn_Table)func_0019E420, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_0019E220,
    (Fn_Table)func_001B9338, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_0019E848, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001BC320, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_0019E418, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_001B8A08, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_001B9F30, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
} };
extern const Fn_Table D_00219DE0[8] = {
    (Fn_Table)func_001A0FE8, 0, 0, (Fn_Table)func_001A1030,
    (Fn_Table)func_001A11C0, (Fn_Table)func_001A1398, (Fn_Table)func_0019ECE0, (Fn_Table)func_0019ED58,
};
extern const ClassDesc_217418<48> D_00219F80 = { (const void*)(const u8*)&D_00217498, 0x4D, 0x1, 0x640, {
    (Fn_Table)func_00139DE8, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_00139E80, (Fn_Table)func_00139EC8,
    (Fn_Table)func_00126F78, (Fn_Table)func_00127048, (Fn_Table)func_001289C0, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_00183350, (Fn_Table)func_001249A8,
    (Fn_Table)func_00124A48, (Fn_Table)func_0013A3A0, (Fn_Table)func_00125108, (Fn_Table)func_00125138,
    (Fn_Table)func_0015FBB8, (Fn_Table)func_001245A8, (Fn_Table)func_00124868, (Fn_Table)func_0013A418,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_0013A940,
    (Fn_Table)func_00125438, (Fn_Table)func_001273F0, (Fn_Table)func_00127478, (Fn_Table)func_001276C0,
    (Fn_Table)func_001274F8, (Fn_Table)func_00127590, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_0013AD08, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_0012B2E8, 0, 0,
} };
extern const ClassDesc_217418<48> D_0021A050 = { (const void*)(const u8*)&D_00217498, 0x50, 0x1, 0x350, {
    (Fn_Table)func_00154C10, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001240F8, (Fn_Table)func_001243E0,
    (Fn_Table)func_00126F78, (Fn_Table)func_00155080, (Fn_Table)func_00154F98, 0,
    0, (Fn_Table)func_00155678, (Fn_Table)func_00183350, (Fn_Table)func_001550E8,
    (Fn_Table)func_00155270, (Fn_Table)func_00155AB0, (Fn_Table)func_00125108, (Fn_Table)func_00125138,
    (Fn_Table)func_0015FBB8, (Fn_Table)func_001245A8, (Fn_Table)func_00124868, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_00125440,
    (Fn_Table)func_00125438, (Fn_Table)func_001273F0, (Fn_Table)func_00127478, (Fn_Table)func_001276C0,
    (Fn_Table)func_001274F8, (Fn_Table)func_00127590, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001261C0, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_0012B2E8, 0, 0,
} };
extern const ClassDesc_217418<28> D_0021A120 = { (const void*)(const u8*)&D_002178C0, 0x77, 0x0, 0x90, {
    (Fn_Table)func_001F39F8, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00182D00, (Fn_Table)func_00182E88, (Fn_Table)func_00182D48, (Fn_Table)func_00182ED0,
    (Fn_Table)func_001830B0, (Fn_Table)func_001830D8, (Fn_Table)func_001F3A40, 0,
    0, 0, (Fn_Table)func_00183350, 0,
    (Fn_Table)func_001585F8, 0, 0, 0,
    0, (Fn_Table)func_001F3A90, (Fn_Table)func_001F3AF0, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001587C0,
} };
extern const ClassDesc_217418<28> D_0021A1A0 = { (const void*)(const u8*)&D_0021A120, 0x78, 0x0, 0xC0, {
    (Fn_Table)func_001F39F8, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00182D00, (Fn_Table)func_00182E88, (Fn_Table)func_00182D48, (Fn_Table)func_00182ED0,
    (Fn_Table)func_001830B0, (Fn_Table)func_00158980, (Fn_Table)func_001587C8, 0,
    0, 0, (Fn_Table)func_00183350, (Fn_Table)func_00158A10,
    (Fn_Table)func_001585F8, 0, 0, 0,
    0, (Fn_Table)func_001F3A90, (Fn_Table)func_001F3AF0, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_00158A80,
} };
extern const ClassDesc_217418<28> D_0021A220 = { (const void*)(const u8*)&D_0021A120, 0x79, 0x0, 0xA0, {
    (Fn_Table)func_00158B00, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00182D00, (Fn_Table)func_00182E88, (Fn_Table)func_00182D48, (Fn_Table)func_00182ED0,
    (Fn_Table)func_001830B0, (Fn_Table)func_00158C28, (Fn_Table)func_00158B30, 0,
    0, 0, (Fn_Table)func_00183350, (Fn_Table)func_00158C60,
    (Fn_Table)func_001585F8, 0, 0, 0,
    0, (Fn_Table)func_001F3A90, (Fn_Table)func_001F3AF0, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_00158D38,
} };
extern const ClassDesc_217418<28> D_0021A2A0 = { (const void*)(const u8*)&D_0021A220, 0x7A, 0x0, 0xD0, {
    (Fn_Table)func_00158E10, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00182D00, (Fn_Table)func_00182E88, (Fn_Table)func_00182D48, (Fn_Table)func_00182ED0,
    (Fn_Table)func_001830B0, (Fn_Table)func_00158C28, (Fn_Table)func_00158B30, 0,
    0, (Fn_Table)func_00158F10, (Fn_Table)func_00183350, (Fn_Table)func_00158E48,
    (Fn_Table)func_001585F8, 0, 0, 0,
    0, (Fn_Table)func_001F3A90, (Fn_Table)func_001F3AF0, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_00158F80,
} };
extern const ClassDesc_217418<48> D_0021A320 = { (const void*)(const u8*)&D_00217498, 0x53, 0x101, 0x2F0, {
    (Fn_Table)func_001963D8, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001240F8, (Fn_Table)func_001243E0,
    (Fn_Table)func_00126F78, (Fn_Table)func_00196810, (Fn_Table)func_00196410, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_00183350, (Fn_Table)func_001249A8,
    (Fn_Table)func_00196900, (Fn_Table)func_00124FC0, (Fn_Table)func_00125108, (Fn_Table)func_00125138,
    (Fn_Table)func_0015FBB8, (Fn_Table)func_001245A8, (Fn_Table)func_00124868, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_00125440,
    (Fn_Table)func_00125438, (Fn_Table)func_001273F0, (Fn_Table)func_00127478, (Fn_Table)func_001276C0,
    (Fn_Table)func_001274F8, (Fn_Table)func_00127590, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001261C0, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_0012B2E8, 0, 0,
} };
extern const ClassDesc_217418<48> D_0021A490 = { (const void*)(const u8*)&D_00217498, 0x65, 0x1, 0x340, {
    (Fn_Table)func_001504E0, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001240F8, (Fn_Table)func_001243E0,
    (Fn_Table)func_00126F78, (Fn_Table)func_00127048, (Fn_Table)func_00150528, 0,
    0, (Fn_Table)func_001512A8, (Fn_Table)func_00183350, (Fn_Table)func_001249A8,
    (Fn_Table)func_001506F0, (Fn_Table)func_00150AE8, (Fn_Table)func_00125108, (Fn_Table)func_00125138,
    (Fn_Table)func_0015FBB8, (Fn_Table)func_001245A8, (Fn_Table)func_00124868, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_00125440,
    (Fn_Table)func_00125438, (Fn_Table)func_001273F0, (Fn_Table)func_00127478, (Fn_Table)func_001276C0,
    (Fn_Table)func_001274F8, (Fn_Table)func_00127590, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001261C0, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_0012B2E8, 0, 0,
} };
extern const ClassDesc_217418<28> D_0021A560 = { (const void*)(const u8*)&D_00217740, 0x6F, 0x0, 0x60, {
    (Fn_Table)func_00169CD8, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00182D00, (Fn_Table)func_00182E88, (Fn_Table)func_00169D20, (Fn_Table)func_00169D58,
    (Fn_Table)func_001830B0, (Fn_Table)func_00169DD8, (Fn_Table)func_001B2840, 0,
    0, 0, (Fn_Table)func_00183350, (Fn_Table)func_00169D90,
    (Fn_Table)func_00182C58, 0, 0, 0,
    0, (Fn_Table)func_001B28A8, 0, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, 0,
} };
extern const ClassDesc_217418<28> D_0021A5E0 = { (const void*)(const u8*)&D_002177C0, 0x7F, 0x0, 0x80, {
    (Fn_Table)func_0016A100, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00182D00, (Fn_Table)func_00182E88, (Fn_Table)func_0016A140, (Fn_Table)func_0016A178,
    (Fn_Table)func_001830B0, (Fn_Table)func_0016A1F8, (Fn_Table)func_00192068, 0,
    0, 0, (Fn_Table)func_00183350, (Fn_Table)func_0016A1B0,
    (Fn_Table)func_00182C58, 0, 0, 0,
    0, (Fn_Table)func_001920E0, (Fn_Table)func_00192128, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, 0,
} };
extern const ClassDesc_217418<72> D_0021A660 = { (const void*)(const u8*)&D_00217568, 0x3A, 0x3, 0x570, {
    (Fn_Table)func_0016A3A8, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_0016A490, (Fn_Table)func_0016A4C8,
    (Fn_Table)func_00126F78, (Fn_Table)func_0016A500, (Fn_Table)func_0016A420, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_00124A48, (Fn_Table)func_001B93F8, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_0016A580, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001B93D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001BC320, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_0016A548, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_001B9F30, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
} };
extern const Fn_Table D_0021A790[10] = {
    (Fn_Table)func_00185358, (Fn_Table)func_001212D8, (Fn_Table)func_00121358, (Fn_Table)func_00185498,
    (Fn_Table)func_001214B8, (Fn_Table)func_00185538, (Fn_Table)func_00121568, (Fn_Table)func_00121580,
    (Fn_Table)func_001215A8, 0,
};
extern const ClassDesc_217418<28> D_0021A7B8 = { (const void*)(const u8*)&D_00217418, 0x8B, 0x0, 0x3F0, {
    (Fn_Table)func_0019C440, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00182D00, (Fn_Table)func_00182E88, (Fn_Table)func_00182D48, (Fn_Table)func_00182ED0,
    (Fn_Table)func_001830B0, (Fn_Table)func_001830D8, (Fn_Table)func_0019C470, 0,
    0, 0, (Fn_Table)func_00183350, 0,
    (Fn_Table)func_0019C728, 0, 0, 0,
    0, (Fn_Table)func_00182F78, 0, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, 0,
} };
extern const ClassDesc_217418<88> D_0021A838 = { (const void*)(const u8*)&D_00217C30, 0x6, 0xB, 0x720, {
    (Fn_Table)func_001C4458, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_00192820, (Fn_Table)func_00192850,
    (Fn_Table)func_00126F78, (Fn_Table)func_001921E8, (Fn_Table)func_001BAC30, 0,
    0, (Fn_Table)func_00192230, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_001C44F0, (Fn_Table)func_001C4ED0, (Fn_Table)func_001C5438, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001C5118, (Fn_Table)func_001B9690, (Fn_Table)func_001C4FA0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001C5DB8,
    (Fn_Table)func_00125C90, (Fn_Table)func_001C49C8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001BC320, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001C4FF8, (Fn_Table)func_001BC760, (Fn_Table)func_001C4F08, (Fn_Table)func_001BC978,
    (Fn_Table)func_001B8A08, (Fn_Table)func_00187F40, (Fn_Table)func_001C5BF0, (Fn_Table)func_001B8B90,
    (Fn_Table)func_001C5338, (Fn_Table)func_001C53E0, (Fn_Table)func_001C5388, (Fn_Table)func_001C57C8,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_00192380, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
    (Fn_Table)func_001922E8, 0, (Fn_Table)func_00192410, (Fn_Table)func_00192450,
    (Fn_Table)func_00192488, (Fn_Table)func_00192490, (Fn_Table)func_001924C8, (Fn_Table)func_001925C0,
    (Fn_Table)func_00192C58, (Fn_Table)func_00192A28, (Fn_Table)func_00192A38, (Fn_Table)func_001930B0,
    (Fn_Table)func_001C53B0, (Fn_Table)func_001C4F00, (Fn_Table)func_001C5248, 0,
} };
extern const Fn_Table D_0021A9A8[10] = {
    (Fn_Table)func_00121338, (Fn_Table)func_001212D8, (Fn_Table)func_00121358, 0,
    (Fn_Table)func_001C5F18, (Fn_Table)func_001C6028, (Fn_Table)func_00121568, (Fn_Table)func_00121580,
    (Fn_Table)func_001215A8, 0,
};
extern const ClassDesc_217418<74> D_0021A9D0 = { (const void*)(const u8*)&D_00218BD8, 0x22, 0x13, 0x6D0, {
    (Fn_Table)func_0013DDB8, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001B7A98, (Fn_Table)func_001B7B78,
    (Fn_Table)func_00126F78, (Fn_Table)func_0013CDE8, (Fn_Table)func_0013CD80, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_0013CE40, (Fn_Table)func_0013D068, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001B9338, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001B93D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_0013D0B0, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_001B8A08, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_001B9F30, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
    (Fn_Table)func_001233C0, 0,
} };
extern const ClassDesc_217418<72> D_0021AB08 = { (const void*)(const u8*)&D_00217568, 0x2F, 0x3, 0x6C0, {
    (Fn_Table)func_00123408, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001B7A98, (Fn_Table)func_001B7B78,
    (Fn_Table)func_00126F78, (Fn_Table)func_00123540, (Fn_Table)func_001BAC30, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_00123448, (Fn_Table)func_00123578, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001B9338, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001B93D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001BC320, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_001B8A08, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_001B9F30, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
} };
extern const ClassDesc_217418<78> D_0021AC38 = { (const void*)(const u8*)&D_00217568, 0x30, 0x3, 0x5D0, {
    (Fn_Table)func_001AECB0, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001B7A98, (Fn_Table)func_001B7B78,
    (Fn_Table)func_00126F78, (Fn_Table)func_001BA130, (Fn_Table)func_001BAC30, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_00124A48, (Fn_Table)func_001AEFA0, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001B9338, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001B93D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001BC320, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_001B8A08, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_001B9F30, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
    0, 0, 0, 0,
    (Fn_Table)func_001AECE0, (Fn_Table)func_001AECE8,
} };
extern const ClassDesc_217418<78> D_0021AD80 = { (const void*)(const u8*)&D_0021AC38, 0x31, 0x3, 0xB10, {
    (Fn_Table)func_001AF0A0, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001B7A98, (Fn_Table)func_001B7B78,
    (Fn_Table)func_00126F78, (Fn_Table)func_001BA130, (Fn_Table)func_001AF0D0, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_001BB210, (Fn_Table)func_001AF108,
    (Fn_Table)func_001AF3B8, (Fn_Table)func_001AF5C8, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_001AF7A8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001B9338, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001AF820, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001BC320, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_001B8A08, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_001B9F30, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
    (Fn_Table)func_001AFBB0, (Fn_Table)func_001B00E8, (Fn_Table)func_001B0120, (Fn_Table)func_001B0160,
    (Fn_Table)func_001AECE0, (Fn_Table)func_001B01B0,
} };
extern const ClassDesc_217418<78> D_0021AEC8 = { (const void*)(const u8*)&D_0021AC38, 0x32, 0x3, 0x5F0, {
    (Fn_Table)func_001B04A0, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001B7A98, (Fn_Table)func_001B7B78,
    (Fn_Table)func_00126F78, (Fn_Table)func_001BA130, (Fn_Table)func_001BAC30, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_001B04D0, (Fn_Table)func_001B0578, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001B9338, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001B0838, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001BC320, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_001B0BD8, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_001B9F30, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
    (Fn_Table)func_001B0C68, (Fn_Table)func_001B0EA8, (Fn_Table)func_001B0EE0, (Fn_Table)func_001B0F70,
    (Fn_Table)func_001AECE0, (Fn_Table)func_001B0FC0,
} };
extern const ClassDesc_217418<78> D_0021B010 = { (const void*)(const u8*)&D_0021AC38, 0x33, 0x3, 0x620, {
    (Fn_Table)func_001B1158, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001B7A98, (Fn_Table)func_001B7B78,
    (Fn_Table)func_00126F78, (Fn_Table)func_001BA130, (Fn_Table)func_001BAC30, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_001B11A0, (Fn_Table)func_001B1238, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001B9338, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001B93D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001BC320, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_001B8A08, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_001B9F30, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
    (Fn_Table)func_001B1438, (Fn_Table)func_001B15D0, (Fn_Table)func_001B1608, (Fn_Table)func_001B1698,
    (Fn_Table)func_001AECE0, (Fn_Table)func_001B1710,
} };
extern const ClassDesc_217418<28> D_0021B158 = { (const void*)(const u8*)&D_002178C0, 0x75, 0x0, 0xA0, {
    (Fn_Table)func_001DFD90, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00182D00, (Fn_Table)func_00182E88, (Fn_Table)func_001DFDC8, (Fn_Table)func_001DFE00,
    (Fn_Table)func_001830B0, (Fn_Table)func_001DFE38, (Fn_Table)func_001F3A40, 0,
    0, 0, (Fn_Table)func_00183350, 0,
    (Fn_Table)func_00182C58, 0, 0, 0,
    0, (Fn_Table)func_001F3A90, (Fn_Table)func_001F3AF0, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, 0,
} };
extern const ClassDesc_217418<28> D_0021B1D8 = { (const void*)(const u8*)&D_0021B158, 0x76, 0x0, 0xC0, {
    (Fn_Table)func_0016C470, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00182D00, (Fn_Table)func_00182E88, (Fn_Table)func_001DFDC8, (Fn_Table)func_001DFE00,
    (Fn_Table)func_001830B0, (Fn_Table)func_001DFE38, (Fn_Table)func_0016C4B8, 0,
    0, 0, (Fn_Table)func_00183350, 0,
    (Fn_Table)func_00182C58, 0, 0, 0,
    0, (Fn_Table)func_001F3A90, (Fn_Table)func_001F3AF0, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, 0,
} };
extern const ClassDesc_217418<28> D_0021B258 = { (const void*)(const u8*)&D_00217740, 0x70, 0x0, 0x70, {
    (Fn_Table)func_00191F08, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00182D00, (Fn_Table)func_00182E88, (Fn_Table)func_00191F68, (Fn_Table)func_00191FA0,
    (Fn_Table)func_001830B0, (Fn_Table)func_00192020, (Fn_Table)func_001B2840, 0,
    0, 0, (Fn_Table)func_00183350, 0,
    (Fn_Table)func_00191FD8, 0, 0, 0,
    0, (Fn_Table)func_001B28A8, 0, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, 0,
} };
extern const ClassDesc_217418<72> D_0021B2D8 = { (const void*)(const u8*)&D_00217568, 0x34, 0x3, 0x5B0, {
    (Fn_Table)func_0012F840, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001B7A98, (Fn_Table)func_001B7B78,
    (Fn_Table)func_00126F78, (Fn_Table)func_0012F888, (Fn_Table)func_001BAC30, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_0012F8C8, (Fn_Table)func_0012F9B8, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001B9338, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001B93D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001BC320, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_0012FA88, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    0, 0, 0, 0,
    0, (Fn_Table)func_0012FB68, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_001B9F30, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
} };
extern const ClassDesc_217418<48> D_0021B408 = { (const void*)(const u8*)&D_00217498, 0x5E, 0x1, 0x340, {
    (Fn_Table)func_001DDCE0, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001240F8, (Fn_Table)func_001243E0,
    (Fn_Table)func_00126F78, (Fn_Table)func_00127048, (Fn_Table)func_001289C0, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_00183350, (Fn_Table)func_001249A8,
    (Fn_Table)func_001DDD18, (Fn_Table)func_00124FC0, (Fn_Table)func_00125108, (Fn_Table)func_00125138,
    (Fn_Table)func_0015FBB8, (Fn_Table)func_001245A8, (Fn_Table)func_00124868, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_00125440,
    (Fn_Table)func_00125438, (Fn_Table)func_001273F0, (Fn_Table)func_00127478, (Fn_Table)func_001DE768,
    (Fn_Table)func_001274F8, (Fn_Table)func_00127590, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001261C0, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001DDE90, (Fn_Table)func_0012B2E8, 0, 0,
} };
extern const ClassDesc_217418<72> D_0021B4D8 = { (const void*)(const u8*)&D_00217568, 0x3B, 0x23, 0x690, {
    (Fn_Table)func_0013B4C0, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001B7A98, (Fn_Table)func_001B7B78,
    (Fn_Table)func_00126F78, (Fn_Table)func_0013B5C8, (Fn_Table)func_0013B598, 0,
    0, (Fn_Table)func_0013B708, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_0013B610, (Fn_Table)func_0013B778, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001B9338, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001B93D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_0013BBA0, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_001B8A08, (Fn_Table)func_00187F40, (Fn_Table)func_0013B9D8, (Fn_Table)func_001B8B90,
    (Fn_Table)func_0013BA70, 0, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_001B9F30, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
} };
extern const ClassDesc_217418<28> D_0021B608 = { (const void*)(const u8*)&D_00217418, 0x8F, 0x0, 0x6C, {
    (Fn_Table)func_0017B998, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00182D00, (Fn_Table)func_00182E88, (Fn_Table)func_00182D48, (Fn_Table)func_00182ED0,
    (Fn_Table)func_001830B0, (Fn_Table)func_001830D8, (Fn_Table)func_001833D0, 0,
    0, 0, (Fn_Table)func_00183350, 0,
    (Fn_Table)func_00182C58, 0, 0, 0,
    0, (Fn_Table)func_00182F78, 0, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, 0,
} };
extern const ClassDesc_217418<88> D_0021B688 = { (const void*)(const u8*)&D_0021A838, 0x7, 0xB, 0x2BF0, {
    (Fn_Table)func_0016F608, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_00178038, (Fn_Table)func_00192850,
    (Fn_Table)func_00126F78, (Fn_Table)func_001921E8, (Fn_Table)func_0016F7B0, 0,
    0, (Fn_Table)func_00170960, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_0016F810, (Fn_Table)func_00174808, (Fn_Table)func_00172530, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_00172B08,
    (Fn_Table)func_001701B0, (Fn_Table)func_00178008, (Fn_Table)func_001C4FA0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001CDF78,
    (Fn_Table)func_001721B0, (Fn_Table)func_001725E0, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001BC320, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_00172B88, (Fn_Table)func_001CD088,
    (Fn_Table)func_001C4FF8, (Fn_Table)func_001BC760, (Fn_Table)func_001C4F08, (Fn_Table)func_001BC978,
    (Fn_Table)func_001B8A08, (Fn_Table)func_00187F40, (Fn_Table)func_00172CF0, (Fn_Table)func_001B8B90,
    (Fn_Table)func_00170410, (Fn_Table)func_00170820, (Fn_Table)func_00170528, (Fn_Table)func_00172898,
    (Fn_Table)func_00170660, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_00172AE0, (Fn_Table)func_00172EE0, (Fn_Table)func_001D6B18, (Fn_Table)func_001BBC30,
    (Fn_Table)func_00173708, (Fn_Table)func_00173888, (Fn_Table)func_00177E20, (Fn_Table)func_001D54E0,
    (Fn_Table)func_001D4D08, (Fn_Table)func_001D65D8, (Fn_Table)func_00177E70, (Fn_Table)func_001925C0,
    (Fn_Table)func_001D6608, (Fn_Table)func_00177EE0, (Fn_Table)func_00177F98, (Fn_Table)func_001930B0,
    (Fn_Table)func_001C53B0, (Fn_Table)func_00172EB8, (Fn_Table)func_00170790, 0,
} };
extern const ClassDesc_217418<28> D_0021B7F8 = { (const void*)(const u8*)&D_002177C0, 0x80, 0x0, 0x70, {
    (Fn_Table)func_00182C18, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00182D00, (Fn_Table)func_00182E88, (Fn_Table)func_0017FD90, (Fn_Table)func_0017FDC8,
    (Fn_Table)func_001830B0, (Fn_Table)func_0017FE00, (Fn_Table)func_00192068, 0,
    0, 0, (Fn_Table)func_00183350, 0,
    (Fn_Table)func_0017FE48, 0, 0, 0,
    0, (Fn_Table)func_001920E0, (Fn_Table)func_00192128, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, 0,
} };
extern const ClassDesc_217418<72> D_0021B878 = { (const void*)(const u8*)&D_0021B4D8, 0x3F, 0x23, 0x6A0, {
    (Fn_Table)func_0013B4C0, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001B7A98, (Fn_Table)func_001B7B78,
    (Fn_Table)func_00126F78, (Fn_Table)func_0013B5C8, (Fn_Table)func_0013B598, 0,
    0, (Fn_Table)func_001D7040, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_0013B610, (Fn_Table)func_0013B778, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001D6DD8, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001B93D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_0013BBA0, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_001D6DA0, (Fn_Table)func_00187F40, (Fn_Table)func_0013B9D8, (Fn_Table)func_001B8B90,
    (Fn_Table)func_001D7018, 0, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_001B9F30, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
} };
extern const ClassDesc_217418<72> D_0021B9A8 = { (const void*)(const u8*)&D_00217568, 0x4C, 0x3, 0x560, {
    (Fn_Table)func_001B7968, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001B7A98, (Fn_Table)func_001B7B78,
    (Fn_Table)func_00126F78, (Fn_Table)func_001BA130, (Fn_Table)func_001BAC30, 0,
    0, (Fn_Table)func_001D3678, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_001D3290, (Fn_Table)func_001D3398, (Fn_Table)func_001B89B8, (Fn_Table)func_001D35A8,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001D3470, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001B93D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001D3500, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_001B8A08, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    0, 0, 0, (Fn_Table)func_001D34E0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_001B9F30, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
} };
extern const ClassDesc_217418<28> D_0021BAD8 = { (const void*)(const u8*)&D_00217418, 0x89, 0x0, 0x190, {
    (Fn_Table)func_001CB618, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00182D00, (Fn_Table)func_00182E88, (Fn_Table)func_00182D48, (Fn_Table)func_00182ED0,
    (Fn_Table)func_001830B0, (Fn_Table)func_001830D8, (Fn_Table)func_001833D0, 0,
    0, 0, (Fn_Table)func_00183350, (Fn_Table)func_001CB7A0,
    (Fn_Table)func_00182C58, 0, 0, 0,
    0, (Fn_Table)func_00182F78, 0, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, 0,
} };
extern const ClassDesc_217418<100> D_0021BB58 = { (const void*)(const u8*)&D_0021A838, 0x8, 0xB, 0xC10, {
    (Fn_Table)func_001C6F48, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001C74E8, (Fn_Table)func_001C7520,
    (Fn_Table)func_00126F78, (Fn_Table)func_001C7188, (Fn_Table)func_001C7140, 0,
    0, (Fn_Table)func_001C9DE0, (Fn_Table)func_001BB210, (Fn_Table)func_001C71E0,
    (Fn_Table)func_001C72A0, (Fn_Table)func_001C7CB8, (Fn_Table)func_001C5438, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001C75B0, (Fn_Table)func_001B9690, (Fn_Table)func_001C4FA0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001C5DB8,
    (Fn_Table)func_00125C90, (Fn_Table)func_001CA5E0, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001C96D8, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001C4FF8, (Fn_Table)func_001BC760, (Fn_Table)func_001C4F08, (Fn_Table)func_001BC978,
    (Fn_Table)func_001C7468, (Fn_Table)func_00187F40, (Fn_Table)func_001CAD98, (Fn_Table)func_001B8B90,
    (Fn_Table)func_001CAC30, (Fn_Table)func_001C53E0, (Fn_Table)func_001CACB0, (Fn_Table)func_001C57C8,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_00192380, (Fn_Table)func_001BA5B0, (Fn_Table)func_001CB3C0,
    (Fn_Table)func_001922E8, 0, (Fn_Table)func_00192410, (Fn_Table)func_001C9A48,
    (Fn_Table)func_001C9990, (Fn_Table)func_00192490, (Fn_Table)func_001924C8, (Fn_Table)func_001925C0,
    (Fn_Table)func_00192C58, (Fn_Table)func_00192A28, (Fn_Table)func_00192A38, (Fn_Table)func_001930B0,
    (Fn_Table)func_001C53B0, (Fn_Table)func_001C4F00, (Fn_Table)func_001C5248, (Fn_Table)func_001CB3C8,
    (Fn_Table)func_001CA460, (Fn_Table)func_001C8010, (Fn_Table)func_001C8E28, (Fn_Table)func_001C9008,
    (Fn_Table)func_001C91C8, (Fn_Table)func_001CA468, (Fn_Table)func_001C8C08, (Fn_Table)func_001C8590,
    (Fn_Table)func_001C9CF8, (Fn_Table)func_001C9AF8, (Fn_Table)func_001CAA08, 0,
} };
extern const ClassDesc_217418<100> D_0021BCF8 = { (const void*)(const u8*)&D_0021BB58, 0xA, 0xB, 0xC50, {
    (Fn_Table)func_00167D68, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001C74E8, (Fn_Table)func_001C7520,
    (Fn_Table)func_00126F78, (Fn_Table)func_001C7188, (Fn_Table)func_001C7140, 0,
    0, (Fn_Table)func_001C9DE0, (Fn_Table)func_001BB210, (Fn_Table)func_001C71E0,
    (Fn_Table)func_00167E08, (Fn_Table)func_001C7CB8, (Fn_Table)func_001C5438, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001C75B0, (Fn_Table)func_001B9690, (Fn_Table)func_001C4FA0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001C5DB8,
    (Fn_Table)func_00125C90, (Fn_Table)func_00167EF0, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001C96D8, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001C4FF8, (Fn_Table)func_001BC760, (Fn_Table)func_001C4F08, (Fn_Table)func_001BC978,
    (Fn_Table)func_001C7468, (Fn_Table)func_00187F40, (Fn_Table)func_001CAD98, (Fn_Table)func_001B8B90,
    (Fn_Table)func_001CAC30, (Fn_Table)func_001C53E0, (Fn_Table)func_001CACB0, (Fn_Table)func_001C57C8,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_00192380, (Fn_Table)func_001BA5B0, (Fn_Table)func_001CB3C0,
    (Fn_Table)func_001922E8, 0, (Fn_Table)func_00192410, (Fn_Table)func_001C9A48,
    (Fn_Table)func_001C9990, (Fn_Table)func_00192490, (Fn_Table)func_001924C8, (Fn_Table)func_001925C0,
    (Fn_Table)func_00192C58, (Fn_Table)func_00192A28, (Fn_Table)func_00192A38, (Fn_Table)func_001930B0,
    (Fn_Table)func_001C53B0, (Fn_Table)func_001C4F00, (Fn_Table)func_001C5248, (Fn_Table)func_00167F10,
    (Fn_Table)func_001CA460, (Fn_Table)func_001C8010, (Fn_Table)func_001C8E28, (Fn_Table)func_001C9008,
    (Fn_Table)func_001C91C8, (Fn_Table)func_001CA468, (Fn_Table)func_001C8C08, (Fn_Table)func_001C8590,
    (Fn_Table)func_001C9CF8, (Fn_Table)func_001C9AF8, (Fn_Table)func_001CAA08, 0,
} };
extern const ClassDesc_217418<100> D_0021BE98 = { (const void*)(const u8*)&D_0021BB58, 0x9, 0xB, 0xD00, {
    (Fn_Table)func_001B6EC8, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001C74E8, (Fn_Table)func_001C7520,
    (Fn_Table)func_00126F78, (Fn_Table)func_001C7188, (Fn_Table)func_001C7140, 0,
    0, (Fn_Table)func_001B78C0, (Fn_Table)func_001BB210, (Fn_Table)func_001C71E0,
    (Fn_Table)func_001B7128, (Fn_Table)func_001B7608, (Fn_Table)func_001C5438, (Fn_Table)func_001B8960,
    (Fn_Table)func_001B7920, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001C75B0, (Fn_Table)func_001B9690, (Fn_Table)func_001C4FA0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001C5DB8,
    (Fn_Table)func_00125C90, (Fn_Table)func_001CA5E0, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001C96D8, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001C4FF8, (Fn_Table)func_001BC760, (Fn_Table)func_001C4F08, (Fn_Table)func_001BC978,
    (Fn_Table)func_001C7468, (Fn_Table)func_00187F40, (Fn_Table)func_001CAD98, (Fn_Table)func_001B8B90,
    (Fn_Table)func_001CAC30, (Fn_Table)func_001C53E0, (Fn_Table)func_001CACB0, (Fn_Table)func_001C57C8,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_00192380, (Fn_Table)func_001BA5B0, (Fn_Table)func_001CB3C0,
    (Fn_Table)func_001922E8, 0, (Fn_Table)func_00192410, (Fn_Table)func_001C9A48,
    (Fn_Table)func_001C9990, (Fn_Table)func_00192490, (Fn_Table)func_001924C8, (Fn_Table)func_001925C0,
    (Fn_Table)func_00192C58, (Fn_Table)func_00192A28, (Fn_Table)func_00192A38, (Fn_Table)func_001930B0,
    (Fn_Table)func_001C53B0, (Fn_Table)func_001C4F00, (Fn_Table)func_001C5248, (Fn_Table)func_001B7280,
    (Fn_Table)func_001B7860, (Fn_Table)func_001C8010, (Fn_Table)func_001C8E28, (Fn_Table)func_001C9008,
    (Fn_Table)func_001B7790, (Fn_Table)func_001B7818, (Fn_Table)func_001C8C08, (Fn_Table)func_001C8590,
    (Fn_Table)func_001C9CF8, (Fn_Table)func_001C9AF8, (Fn_Table)func_001CAA08, 0,
} };
extern const ClassDesc_217418<72> D_0021C038 = { (const void*)(const u8*)&D_00217568, 0x36, 0x3, 0x860, {
    (Fn_Table)func_001F4F70, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001B7A98, (Fn_Table)func_001B7B78,
    (Fn_Table)func_00126F78, (Fn_Table)func_001F51A0, (Fn_Table)func_001BAC30, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_001F4FD8, (Fn_Table)func_001F5008, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001B9338, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_001F51C8, (Fn_Table)func_001B93D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001BC320, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_001B8A08, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_001B9F30, (Fn_Table)func_001BA5B0, (Fn_Table)func_001F51E8,
} };
extern const ClassDesc_217418<72> D_0021C168 = { (const void*)(const u8*)&D_0021C038, 0x37, 0x3, 0x860, {
    (Fn_Table)func_001F5218, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001B7A98, (Fn_Table)func_001B7B78,
    (Fn_Table)func_00126F78, (Fn_Table)func_001F51A0, (Fn_Table)func_001BAC30, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_001F4FD8, (Fn_Table)func_001F5268, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001B9338, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_001F51C8, (Fn_Table)func_001B93D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001BC320, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_001B8A08, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_001B9F30, (Fn_Table)func_001BA5B0, (Fn_Table)func_001F51E8,
} };
extern const ClassDesc_217418<28> D_0021C298 = { (const void*)(const u8*)&D_002178C0, 0x7B, 0x0, 0x90, {
    (Fn_Table)func_001F39F8, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00182D00, (Fn_Table)func_00182E88, (Fn_Table)func_00182D48, (Fn_Table)func_00182ED0,
    (Fn_Table)func_001830B0, (Fn_Table)func_001830D8, (Fn_Table)func_00141108, 0,
    0, 0, (Fn_Table)func_00183350, 0,
    (Fn_Table)func_00182C58, 0, 0, 0,
    0, (Fn_Table)func_001F3A90, (Fn_Table)func_001F3AF0, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, 0,
} };
extern const ClassDesc_217418<72> D_0021C318 = { (const void*)(const u8*)&D_00217568, 0x38, 0x3, 0x5C0, {
    (Fn_Table)func_001411A8, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001B7A98, (Fn_Table)func_001B7B78,
    (Fn_Table)func_00126F78, (Fn_Table)func_001415D0, (Fn_Table)func_00141210, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_001BB210, (Fn_Table)func_00141338,
    (Fn_Table)func_00141438, (Fn_Table)func_00141690, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001B9338, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001B93D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001417F0, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_001B8A08, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_001B9F30, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
} };
extern const ClassDesc_217418<28> D_0021C448 = { (const void*)(const u8*)&D_00217418, 0x8A, 0x0, 0x58, {
    (Fn_Table)func_00182C18, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00182D00, (Fn_Table)func_00182E88, (Fn_Table)func_00182D48, (Fn_Table)func_00182ED0,
    (Fn_Table)func_001830B0, (Fn_Table)func_001830D8, (Fn_Table)func_001916D0, 0,
    0, 0, (Fn_Table)func_00183350, 0,
    (Fn_Table)func_00182C58, 0, 0, 0,
    0, (Fn_Table)func_00182F78, 0, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, 0,
} };
extern const ClassDesc_217418<48> D_0021C4C8 = { (const void*)(const u8*)&D_00217498, 0x54, 0x1, 0x2E0, {
    (Fn_Table)func_00123ED0, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001240F8, (Fn_Table)func_001243E0,
    (Fn_Table)func_00126F78, (Fn_Table)func_00127048, (Fn_Table)func_001289C0, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_00183350, (Fn_Table)func_001249A8,
    (Fn_Table)func_001B5CD8, (Fn_Table)func_001B5D28, (Fn_Table)func_00125108, (Fn_Table)func_00125138,
    (Fn_Table)func_0015FBB8, (Fn_Table)func_001245A8, (Fn_Table)func_00124868, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_00125440,
    (Fn_Table)func_00125438, (Fn_Table)func_001273F0, (Fn_Table)func_00127478, (Fn_Table)func_001276C0,
    (Fn_Table)func_001274F8, (Fn_Table)func_00127590, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001261C0, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_0012B2E8, 0, 0,
} };
extern const ClassDesc_217418<72> D_0021C598 = { (const void*)(const u8*)&D_00217568, 0x40, 0x3, 0x6A0, {
    (Fn_Table)func_0015AAE0, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001B7A98, (Fn_Table)func_001B7B78,
    (Fn_Table)func_00126F78, (Fn_Table)func_0015AD80, (Fn_Table)func_0015AC08, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_0015AEB0, (Fn_Table)func_0015B128, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015AE38, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_0015AF50, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_0015B4D0, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_0015B720, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_001B8A08, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_001B9F30, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
} };
extern const ClassDesc_217418<48> D_0021C6C8 = { (const void*)(const u8*)&D_00217498, 0x55, 0x1, 0x390, {
    (Fn_Table)func_00146340, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001240F8, (Fn_Table)func_001243E0,
    (Fn_Table)func_00126F78, (Fn_Table)func_00146418, (Fn_Table)func_001463C0, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_00183350, (Fn_Table)func_001249A8,
    (Fn_Table)func_00146470, (Fn_Table)func_00147428, (Fn_Table)func_00125108, (Fn_Table)func_00125138,
    (Fn_Table)func_0015FBB8, (Fn_Table)func_001245A8, (Fn_Table)func_00124868, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_00146518,
    (Fn_Table)func_00125438, (Fn_Table)func_001273F0, (Fn_Table)func_00127478, (Fn_Table)func_001276C0,
    (Fn_Table)func_001274F8, (Fn_Table)func_00127590, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_001478F0, (Fn_Table)func_001261C0, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001473E0, 0, (Fn_Table)func_00147AB0,
} };
extern const ClassDesc_217418<48> D_0021C798 = { (const void*)(const u8*)&D_0021C6C8, 0x58, 0x1, 0x3A0, {
    (Fn_Table)func_00147E40, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001240F8, (Fn_Table)func_001243E0,
    (Fn_Table)func_00126F78, (Fn_Table)func_00146418, (Fn_Table)func_001463C0, 0,
    0, (Fn_Table)func_00147EF8, (Fn_Table)func_00183350, (Fn_Table)func_001249A8,
    (Fn_Table)func_00146470, (Fn_Table)func_00147FB0, (Fn_Table)func_00125108, (Fn_Table)func_00125138,
    (Fn_Table)func_0015FBB8, (Fn_Table)func_001245A8, (Fn_Table)func_00124868, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_00146518,
    (Fn_Table)func_00125438, (Fn_Table)func_001273F0, (Fn_Table)func_00127478, (Fn_Table)func_001276C0,
    (Fn_Table)func_001274F8, (Fn_Table)func_00127590, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_001478F0, (Fn_Table)func_001261C0, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001473E0, 0, (Fn_Table)func_00148298,
} };
extern const ClassDesc_217418<48> D_0021C868 = { (const void*)(const u8*)&D_0021C6C8, 0x56, 0x1, 0x390, {
    (Fn_Table)func_00148400, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001240F8, (Fn_Table)func_001243E0,
    (Fn_Table)func_00126F78, (Fn_Table)func_00146418, (Fn_Table)func_001463C0, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_00183350, (Fn_Table)func_001249A8,
    (Fn_Table)func_00146470, (Fn_Table)func_00147428, (Fn_Table)func_00125108, (Fn_Table)func_00125138,
    (Fn_Table)func_0015FBB8, (Fn_Table)func_001245A8, (Fn_Table)func_00124868, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_00146518,
    (Fn_Table)func_00125438, (Fn_Table)func_001273F0, (Fn_Table)func_00127478, (Fn_Table)func_001276C0,
    (Fn_Table)func_001274F8, (Fn_Table)func_00127590, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_001478F0, (Fn_Table)func_001261C0, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001473E0, 0, (Fn_Table)func_00148470,
} };
extern const ClassDesc_217418<48> D_0021C938 = { (const void*)(const u8*)&D_0021C6C8, 0x59, 0x1, 0x390, {
    (Fn_Table)func_00148510, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001240F8, (Fn_Table)func_001243E0,
    (Fn_Table)func_00126F78, (Fn_Table)func_00146418, (Fn_Table)func_001463C0, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_00183350, (Fn_Table)func_001249A8,
    (Fn_Table)func_00146470, (Fn_Table)func_00147428, (Fn_Table)func_00125108, (Fn_Table)func_00125138,
    (Fn_Table)func_0015FBB8, (Fn_Table)func_001245A8, (Fn_Table)func_00124868, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_00146518,
    (Fn_Table)func_00125438, (Fn_Table)func_001273F0, (Fn_Table)func_00127478, (Fn_Table)func_001276C0,
    (Fn_Table)func_001274F8, (Fn_Table)func_00127590, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_001478F0, (Fn_Table)func_001261C0, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001473E0, 0, (Fn_Table)func_00148598,
} };
extern const ClassDesc_217418<48> D_0021CA08 = { (const void*)(const u8*)&D_0021C6C8, 0x5A, 0x1, 0x390, {
    (Fn_Table)func_00148698, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001240F8, (Fn_Table)func_001243E0,
    (Fn_Table)func_00126F78, (Fn_Table)func_00146418, (Fn_Table)func_001463C0, 0,
    0, (Fn_Table)func_00148770, (Fn_Table)func_00183350, (Fn_Table)func_001249A8,
    (Fn_Table)func_00148718, (Fn_Table)func_00148828, (Fn_Table)func_00125108, (Fn_Table)func_00125138,
    (Fn_Table)func_0015FBB8, (Fn_Table)func_001245A8, (Fn_Table)func_00124868, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_00146518,
    (Fn_Table)func_00125438, (Fn_Table)func_001273F0, (Fn_Table)func_00127478, (Fn_Table)func_001276C0,
    (Fn_Table)func_001274F8, (Fn_Table)func_00127590, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_001478F0, (Fn_Table)func_001261C0, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001473E0, 0, (Fn_Table)func_00148888,
} };
extern const ClassDesc_217418<48> D_0021CAD8 = { (const void*)(const u8*)&D_0021C6C8, 0x57, 0x1, 0x3A0, {
    (Fn_Table)func_00148D90, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001240F8, (Fn_Table)func_001243E0,
    (Fn_Table)func_00126F78, (Fn_Table)func_00146418, (Fn_Table)func_001463C0, 0,
    0, (Fn_Table)func_00148E40, (Fn_Table)func_00183350, (Fn_Table)func_001249A8,
    (Fn_Table)func_00146470, (Fn_Table)func_00148EF8, (Fn_Table)func_00125108, (Fn_Table)func_00125138,
    (Fn_Table)func_0015FBB8, (Fn_Table)func_001245A8, (Fn_Table)func_00124868, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_00146518,
    (Fn_Table)func_00125438, (Fn_Table)func_001273F0, (Fn_Table)func_00127478, (Fn_Table)func_001276C0,
    (Fn_Table)func_001274F8, (Fn_Table)func_00127590, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_001478F0, (Fn_Table)func_001261C0, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001473E0, 0, (Fn_Table)func_00148FF0,
} };
extern const ClassDesc_217418<48> D_0021CBA8 = { (const void*)(const u8*)&D_0021C6C8, 0x5B, 0x1, 0x390, {
    (Fn_Table)func_00149168, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001240F8, (Fn_Table)func_001243E0,
    (Fn_Table)func_00126F78, (Fn_Table)func_00146418, (Fn_Table)func_001463C0, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_00183350, (Fn_Table)func_001249A8,
    (Fn_Table)func_00146470, (Fn_Table)func_00149190, (Fn_Table)func_00125108, (Fn_Table)func_00125138,
    (Fn_Table)func_0015FBB8, (Fn_Table)func_001245A8, (Fn_Table)func_00124868, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_00146518,
    (Fn_Table)func_00125438, (Fn_Table)func_001273F0, (Fn_Table)func_00127478, (Fn_Table)func_001276C0,
    (Fn_Table)func_001274F8, (Fn_Table)func_00127590, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_001478F0, (Fn_Table)func_001261C0, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001473E0, 0, (Fn_Table)func_00147AB0,
} };
extern const ClassDesc_217418<76> D_0021CC78 = { (const void*)(const u8*)&D_00217568, 0x2C, 0x3, 0x5A0, {
    (Fn_Table)func_00198980, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001B7A98, (Fn_Table)func_001B7B78,
    (Fn_Table)func_00126F78, (Fn_Table)func_001BA130, (Fn_Table)func_001989B0, 0,
    0, (Fn_Table)func_00198EF8, (Fn_Table)func_001BB210, (Fn_Table)func_00198A88,
    (Fn_Table)func_00198B28, (Fn_Table)func_00198BD8, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001B9338, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001B93D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001BC320, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_00198FB0, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    (Fn_Table)func_00199000, 0, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_001B9F30, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
    (Fn_Table)func_00198E98, (Fn_Table)func_00198DA8, (Fn_Table)func_00198E58, 0,
} };
extern const ClassDesc_217418<76> D_0021CDB8 = { (const void*)(const u8*)&D_0021CC78, 0x2D, 0x3, 0x5B0, {
    (Fn_Table)func_00199070, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001B7A98, (Fn_Table)func_001B7B78,
    (Fn_Table)func_00126F78, (Fn_Table)func_001990A8, (Fn_Table)func_001989B0, 0,
    0, (Fn_Table)func_00198EF8, (Fn_Table)func_001BB210, (Fn_Table)func_00198A88,
    (Fn_Table)func_00198B28, (Fn_Table)func_00198BD8, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001B9338, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001B93D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001BC320, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_00198FB0, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    (Fn_Table)func_00199000, 0, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_001B9F30, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
    (Fn_Table)func_001990E0, (Fn_Table)func_00199138, (Fn_Table)func_00198E58, 0,
} };
extern const ClassDesc_217418<76> D_0021CEF8 = { (const void*)(const u8*)&D_0021CC78, 0x2E, 0x3, 0x5C0, {
    (Fn_Table)func_001993F0, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001B7A98, (Fn_Table)func_001B7B78,
    (Fn_Table)func_00126F78, (Fn_Table)func_001994C8, (Fn_Table)func_00199428, 0,
    0, (Fn_Table)func_00198EF8, (Fn_Table)func_001BB210, (Fn_Table)func_00198A88,
    (Fn_Table)func_00199500, (Fn_Table)func_00199698, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001B9338, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00199D08, (Fn_Table)func_001B93D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_00199C78, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_00199C58, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_00198FB0, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    (Fn_Table)func_00199000, 0, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_001B9F30, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
    (Fn_Table)func_00198E98, (Fn_Table)func_001999D0, (Fn_Table)func_00198E58, 0,
} };
extern const ClassDesc_217418<48> D_0021D038 = { (const void*)(const u8*)&D_00217498, 0x5C, 0x1, 0x2E0, {
    (Fn_Table)func_00123ED0, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001240F8, (Fn_Table)func_001243E0,
    (Fn_Table)func_00126F78, (Fn_Table)func_00127048, (Fn_Table)func_00199170, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_00183350, (Fn_Table)func_001249A8,
    (Fn_Table)func_001991A8, (Fn_Table)func_00124FC0, (Fn_Table)func_00125108, (Fn_Table)func_00125138,
    (Fn_Table)func_0015FBB8, (Fn_Table)func_001245A8, (Fn_Table)func_00124868, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_00125440,
    (Fn_Table)func_00125438, (Fn_Table)func_001273F0, (Fn_Table)func_00127478, (Fn_Table)func_001276C0,
    (Fn_Table)func_001274F8, (Fn_Table)func_00127590, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001261C0, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_0012B2E8, 0, 0,
} };
extern const ClassDesc_217418<48> D_0021D108 = { (const void*)(const u8*)&D_00217498, 0x5D, 0x1, 0x330, {
    (Fn_Table)func_00123ED0, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001240F8, (Fn_Table)func_001243E0,
    (Fn_Table)func_00126F78, (Fn_Table)func_00127048, (Fn_Table)func_001991E0, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_00183350, (Fn_Table)func_001249A8,
    (Fn_Table)func_00199218, (Fn_Table)func_00124FC0, (Fn_Table)func_00125108, (Fn_Table)func_00125138,
    (Fn_Table)func_0015FBB8, (Fn_Table)func_001245A8, (Fn_Table)func_00124868, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_00125440,
    (Fn_Table)func_00125438, (Fn_Table)func_001273F0, (Fn_Table)func_00127478, (Fn_Table)func_001276C0,
    (Fn_Table)func_001274F8, (Fn_Table)func_00127590, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001261C0, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_0012B2E8, 0, 0,
} };
extern const ClassDesc_217418<84> D_0021D1D8 = { (const void*)(const u8*)&D_00217C30, 0x17, 0xB, 0x800, {
    (Fn_Table)func_0019A148, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_00192820, (Fn_Table)func_00192850,
    (Fn_Table)func_00126F78, (Fn_Table)func_001921E8, (Fn_Table)func_001BAC30, 0,
    0, (Fn_Table)func_0019AB78, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_0019A1E0, (Fn_Table)func_00192B58, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001B9338, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001B93D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001BC320, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_001B8A08, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_00192380, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
    (Fn_Table)func_0019A520, (Fn_Table)func_0019A6A8, (Fn_Table)func_00192410, (Fn_Table)func_00192450,
    (Fn_Table)func_00192488, (Fn_Table)func_00192490, (Fn_Table)func_001924C8, (Fn_Table)func_001925C0,
    (Fn_Table)func_00192C58, (Fn_Table)func_00192A28, (Fn_Table)func_00192A38, (Fn_Table)func_001930B0,
} };
extern const ClassDesc_217418<28> D_0021D338 = { (const void*)(const u8*)&D_0021C298, 0x7C, 0x0, 0xA0, {
    (Fn_Table)func_001F39F8, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00182D00, (Fn_Table)func_00182E88, (Fn_Table)func_0019C3D0, (Fn_Table)func_0019C408,
    (Fn_Table)func_001830B0, (Fn_Table)func_001830D8, (Fn_Table)func_00141108, 0,
    0, 0, (Fn_Table)func_00183350, 0,
    (Fn_Table)func_00182C58, 0, 0, 0,
    0, (Fn_Table)func_001F3A90, (Fn_Table)func_001F3AF0, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, 0,
} };
extern const ClassDesc_217418<72> D_0021D3B8 = { (const void*)(const u8*)&D_00217568, 0x41, 0x3, 0x670, {
    (Fn_Table)func_0019B038, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_0019B1E0, (Fn_Table)func_0019B218,
    (Fn_Table)func_00126F78, (Fn_Table)func_0019B250, (Fn_Table)func_0019B0A0, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_0019B188, (Fn_Table)func_0019B378, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_0019B298, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_0019BC40, (Fn_Table)func_001B93D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_0019BE08, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_001B8A08, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    (Fn_Table)func_0019BB10, (Fn_Table)func_0019BB90, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_001B9F30, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
} };
extern const ClassDesc_217418<48> D_0021D4E8 = { (const void*)(const u8*)&D_00217498, 0x5F, 0x1, 0x660, {
    (Fn_Table)func_001A4718, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001240F8, (Fn_Table)func_001243E0,
    (Fn_Table)func_00126F78, (Fn_Table)func_00127048, (Fn_Table)func_001289C0, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_00183350, (Fn_Table)func_001A48C0,
    (Fn_Table)func_001A4B30, (Fn_Table)func_001A4C48, (Fn_Table)func_00125108, (Fn_Table)func_00125138,
    (Fn_Table)func_0015FBB8, (Fn_Table)func_001245A8, (Fn_Table)func_00124868, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_00125440,
    (Fn_Table)func_00125438, (Fn_Table)func_001273F0, (Fn_Table)func_00127478, (Fn_Table)func_001276C0,
    (Fn_Table)func_001274F8, (Fn_Table)func_00127590, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001261C0, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_0012B2E8, (Fn_Table)func_001A4D60, 0,
} };
extern const ClassDesc_217418<84> D_0021D5B8 = { (const void*)(const u8*)&D_00217C30, 0x15, 0xB, 0x690, {
    (Fn_Table)func_001A3AE0, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_00192820, (Fn_Table)func_00192850,
    (Fn_Table)func_00126F78, (Fn_Table)func_001921E8, (Fn_Table)func_001A3B20, 0,
    0, (Fn_Table)func_001A43C8, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_001A3B58, (Fn_Table)func_001A3D40, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001A44E8, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001B93D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001BC320, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001A4610, (Fn_Table)func_001BC978,
    (Fn_Table)func_001B8A08, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    (Fn_Table)func_001A45B8, (Fn_Table)func_001A4538, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_00192380, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
    (Fn_Table)func_001922E8, (Fn_Table)func_001A3C40, (Fn_Table)func_001A4710, (Fn_Table)func_00192450,
    (Fn_Table)func_00192488, (Fn_Table)func_00192490, (Fn_Table)func_001924C8, (Fn_Table)func_001925C0,
    (Fn_Table)func_00192C58, (Fn_Table)func_00192A28, (Fn_Table)func_00192A38, (Fn_Table)func_001930B0,
} };
extern const ClassDesc_217418<72> D_0021D718 = { (const void*)(const u8*)&D_00217568, 0x42, 0x3, 0x5C0, {
    (Fn_Table)func_001A6498, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001B7A98, (Fn_Table)func_001B7B78,
    (Fn_Table)func_00126F78, (Fn_Table)func_001A6540, (Fn_Table)func_001A64F8, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_001A6588, (Fn_Table)func_001A65C8, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001B9338, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001B93D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001A6DE0, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_001B8A08, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_001B9F30, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
} };
extern const ClassDesc_217418<72> D_0021D848 = { (const void*)(const u8*)&D_00217568, 0x43, 0x3, 0x5B0, {
    (Fn_Table)func_001A6F88, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001B7A98, (Fn_Table)func_001B7B78,
    (Fn_Table)func_00126F78, (Fn_Table)func_001A7050, (Fn_Table)func_001A7008, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_001A7098, (Fn_Table)func_001A7128, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001A7230, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001B93D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001A72B0, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_001B8A08, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    (Fn_Table)func_001A7290, 0, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_001B9F30, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
} };
extern const ClassDesc_217418<72> D_0021D978 = { (const void*)(const u8*)&D_00217568, 0x44, 0x3, 0x570, {
    (Fn_Table)func_001A7520, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001B7A98, (Fn_Table)func_001B7B78,
    (Fn_Table)func_00126F78, (Fn_Table)func_001A7588, (Fn_Table)func_001A7550, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_001A75D0, (Fn_Table)func_001A7648, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001B9338, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001B93D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001BC320, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_001B8A08, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_001B9F30, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
} };
extern const ClassDesc_217418<72> D_0021DAA8 = { (const void*)(const u8*)&D_00217568, 0x45, 0x3, 0x570, {
    (Fn_Table)func_001A7708, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001B7A98, (Fn_Table)func_001B7B78,
    (Fn_Table)func_00126F78, (Fn_Table)func_001BA130, (Fn_Table)func_001A7750, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_001A7798, (Fn_Table)func_001A7800, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001B9338, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001B93D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001BC320, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_001B8A08, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_001B9F30, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
} };
extern const ClassDesc_217418<72> D_0021DBD8 = { (const void*)(const u8*)&D_00217568, 0x46, 0x3, 0x590, {
    (Fn_Table)func_0014EE40, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_0014EF00,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_0014EE70, (Fn_Table)func_001B7B78,
    (Fn_Table)func_00126F78, (Fn_Table)func_0014EF40, (Fn_Table)func_0014EF88, 0,
    0, (Fn_Table)func_0014EFB8, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_0014F020, (Fn_Table)func_0014F058, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001B9338, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001B93D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001BC320, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_001B8A08, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_001B9F30, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
} };
extern const ClassDesc_217418<74> D_0021DD08 = { (const void*)(const u8*)&D_00218BD8, 0x23, 0x13, 0x7C0, {
    (Fn_Table)func_0014F740, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001B7A98, (Fn_Table)func_001B7B78,
    (Fn_Table)func_00126F78, (Fn_Table)func_0013CDE8, (Fn_Table)func_0013CD80, 0,
    0, (Fn_Table)func_0014F770, (Fn_Table)func_001BB210, (Fn_Table)func_0014F850,
    (Fn_Table)func_0014F920, (Fn_Table)func_0014FA88, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001B9338, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001B93D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_0013D0B0, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_0014FBE0, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_001B9F30, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
    (Fn_Table)func_0014FC38, 0,
} };
extern const ClassDesc_217418<48> D_0021DE40 = { (const void*)(const u8*)&D_00217498, 0x60, 0x1, 0x300, {
    (Fn_Table)func_0015A8B8, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001240F8, (Fn_Table)func_001243E0,
    (Fn_Table)func_00126F78, (Fn_Table)func_00127048, (Fn_Table)func_0015A918, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_00183350, (Fn_Table)func_001249A8,
    (Fn_Table)func_00124A48, (Fn_Table)func_0015A960, (Fn_Table)func_00125108, (Fn_Table)func_00125138,
    (Fn_Table)func_0015FBB8, (Fn_Table)func_001245A8, (Fn_Table)func_00124868, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_00125440,
    (Fn_Table)func_00125438, (Fn_Table)func_001273F0, (Fn_Table)func_00127478, (Fn_Table)func_001276C0,
    (Fn_Table)func_001274F8, (Fn_Table)func_00127590, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_0015A9A8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_0012B2E8, 0, 0,
} };
extern const ClassDesc_217418<74> D_0021DF10 = { (const void*)(const u8*)&D_0021B4D8, 0x3C, 0x23, 0x6F0, {
    (Fn_Table)func_0018D8E0, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001B7A98, (Fn_Table)func_0018D978,
    (Fn_Table)func_00126F78, (Fn_Table)func_0013B5C8, (Fn_Table)func_0018D910, 0,
    0, (Fn_Table)func_0013B708, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_0013B610, (Fn_Table)func_0013B778, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_0018D9B8,
    (Fn_Table)func_001B9338, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_0018DB20, (Fn_Table)func_001B93D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_0013BBA0, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_0018DC88, (Fn_Table)func_00187F40, (Fn_Table)func_0013B9D8, (Fn_Table)func_001B8B90,
    (Fn_Table)func_0013BA70, 0, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_001B9F30, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
    (Fn_Table)func_0018DA40, 0,
} };
extern const ClassDesc_217418<74> D_0021E048 = { (const void*)(const u8*)&D_0021DF10, 0x3D, 0x23, 0x710, {
    (Fn_Table)func_0018DDA0, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001B7A98, (Fn_Table)func_0018D978,
    (Fn_Table)func_00126F78, (Fn_Table)func_0013B5C8, (Fn_Table)func_0018D910, 0,
    0, (Fn_Table)func_0013B708, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_0013B610, (Fn_Table)func_0013B778, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_0018D9B8,
    (Fn_Table)func_0018DE70, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_0018DB20, (Fn_Table)func_001B93D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_0013BBA0, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_0018DC88, (Fn_Table)func_00187F40, (Fn_Table)func_0013B9D8, (Fn_Table)func_001B8B90,
    (Fn_Table)func_0013BA70, 0, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_001B9F30, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
    (Fn_Table)func_0018DDD8, 0,
} };
extern const ClassDesc_217418<74> D_0021E180 = { (const void*)(const u8*)&D_0021DF10, 0x3E, 0x23, 0x710, {
    (Fn_Table)func_0018D8E0, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001B7A98, (Fn_Table)func_0018D978,
    (Fn_Table)func_00126F78, (Fn_Table)func_0013B5C8, (Fn_Table)func_0018D910, 0,
    0, (Fn_Table)func_0013B708, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_0013B610, (Fn_Table)func_0013B778, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_0018E040,
    (Fn_Table)func_001B9338, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_0018DB20, (Fn_Table)func_001B93D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_0013BBA0, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_0018DC88, (Fn_Table)func_00187F40, (Fn_Table)func_0013B9D8, (Fn_Table)func_001B8B90,
    (Fn_Table)func_0013BA70, 0, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_001B9F30, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
    (Fn_Table)func_0018DEE8, 0,
} };
extern const ClassDesc_217418<36> D_0021E2B8 = { (const void*)(const u8*)&D_00217418, 0x8C, 0x0, 0x170, {
    (Fn_Table)func_001A7FE8, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00182D00, (Fn_Table)func_00182E88, (Fn_Table)func_00182D48, (Fn_Table)func_001A80E0,
    (Fn_Table)func_001830B0, (Fn_Table)func_001A84C8, (Fn_Table)func_001833D0, 0,
    0, 0, (Fn_Table)func_00183350, 0,
    (Fn_Table)func_001A8590, 0, 0, 0,
    (Fn_Table)func_001A86F8, (Fn_Table)func_00182F78, 0, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, 0,
    (Fn_Table)func_001B4AA0, (Fn_Table)func_001B4AD0, 0, (Fn_Table)func_001B4B38,
    0, (Fn_Table)func_001B4B48, 0, 0,
} };
extern const Fn_Table D_0021E438[8] = {
    (Fn_Table)func_00159680, (Fn_Table)func_001596E0, (Fn_Table)func_00159890, (Fn_Table)func_001B4B38,
    0, (Fn_Table)func_00159A80, 0, 0,
};
extern const ClassDesc_217418<72> D_0021E458 = { (const void*)(const u8*)&D_00217568, 0x39, 0x3, 0x560, {
    (Fn_Table)func_00146100, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001B7A98, (Fn_Table)func_001B7B78,
    (Fn_Table)func_00126F78, (Fn_Table)func_001BA130, (Fn_Table)func_00146130, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_00146178, (Fn_Table)func_001B93F8, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001B9338, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001B93D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001BC320, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_001B8A08, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    0, (Fn_Table)func_001461A8, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_001B9F30, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
} };
extern const ClassDesc_217418<48> D_0021E588 = { (const void*)(const u8*)&D_00217498, 0x61, 0x1, 0x2F0, {
    (Fn_Table)func_00152E28, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001240F8, (Fn_Table)func_001243E0,
    (Fn_Table)func_00126F78, (Fn_Table)func_00127048, (Fn_Table)func_001289C0, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_00183350, (Fn_Table)func_001249A8,
    (Fn_Table)func_00124A48, (Fn_Table)func_00124FC0, (Fn_Table)func_00125108, (Fn_Table)func_00125138,
    (Fn_Table)func_0015FBB8, (Fn_Table)func_001245A8, (Fn_Table)func_00124868, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_00125440,
    (Fn_Table)func_00125438, (Fn_Table)func_001273F0, (Fn_Table)func_00127478, (Fn_Table)func_001276C0,
    (Fn_Table)func_001274F8, (Fn_Table)func_00127590, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_00153328, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_0012B2E8, 0, 0,
} };
extern const ClassDesc_217418<48> D_0021E658 = { (const void*)(const u8*)&D_00217498, 0x62, 0x1, 0x330, {
    (Fn_Table)func_001EF838, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001240F8, (Fn_Table)func_001243E0,
    (Fn_Table)func_00126F78, (Fn_Table)func_00127048, (Fn_Table)func_001289C0, 0,
    0, (Fn_Table)func_001EF9C8, (Fn_Table)func_00183350, (Fn_Table)func_001249A8,
    (Fn_Table)func_001EF868, (Fn_Table)func_001EF8F8, (Fn_Table)func_00125108, (Fn_Table)func_00125138,
    (Fn_Table)func_0015FBB8, (Fn_Table)func_001245A8, (Fn_Table)func_00124868, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_00125440,
    (Fn_Table)func_00125438, (Fn_Table)func_001273F0, (Fn_Table)func_00127478, (Fn_Table)func_001276C0,
    (Fn_Table)func_001274F8, (Fn_Table)func_00127590, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001261C0, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_0012B2E8, 0, 0,
} };
extern const ClassDesc_217418<100> D_0021E728 = { (const void*)(const u8*)&D_0021BCF8, 0xB, 0xB, 0xCA0, {
    (Fn_Table)func_001E88D0, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001C74E8, (Fn_Table)func_001C7520,
    (Fn_Table)func_00126F78, (Fn_Table)func_001C7188, (Fn_Table)func_001C7140, 0,
    0, (Fn_Table)func_001C9DE0, (Fn_Table)func_001BB210, (Fn_Table)func_001C71E0,
    (Fn_Table)func_001E8948, (Fn_Table)func_001C7CB8, (Fn_Table)func_001C5438, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001C75B0, (Fn_Table)func_001B9690, (Fn_Table)func_001C4FA0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001C5DB8,
    (Fn_Table)func_00125C90, (Fn_Table)func_00167EF0, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001C96D8, (Fn_Table)func_001E8FE8, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001C4FF8, (Fn_Table)func_001BC760, (Fn_Table)func_001C4F08, (Fn_Table)func_001BC978,
    (Fn_Table)func_001E9038, (Fn_Table)func_00187F40, (Fn_Table)func_001CAD98, (Fn_Table)func_001B8B90,
    (Fn_Table)func_001CAC30, (Fn_Table)func_001C53E0, (Fn_Table)func_001CACB0, (Fn_Table)func_001C57C8,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_00192380, (Fn_Table)func_001BA5B0, (Fn_Table)func_001CB3C0,
    (Fn_Table)func_001922E8, 0, (Fn_Table)func_00192410, (Fn_Table)func_001C9A48,
    (Fn_Table)func_001C9990, (Fn_Table)func_00192490, (Fn_Table)func_001924C8, (Fn_Table)func_001925C0,
    (Fn_Table)func_00192C58, (Fn_Table)func_00192A28, (Fn_Table)func_00192A38, (Fn_Table)func_001930B0,
    (Fn_Table)func_001C53B0, (Fn_Table)func_001C4F00, (Fn_Table)func_001C5248, (Fn_Table)func_001E8DB0,
    (Fn_Table)func_001CA460, (Fn_Table)func_001E8D58, (Fn_Table)func_001E8FA8, (Fn_Table)func_001C9008,
    (Fn_Table)func_001E8A50, (Fn_Table)func_001E8DD0, (Fn_Table)func_001E8EF8, (Fn_Table)func_001C8590,
    (Fn_Table)func_001E8E48, (Fn_Table)func_001E8E08, (Fn_Table)func_001CAA08, 0,
} };
extern const ClassDesc_217418<100> D_0021E8C8 = { (const void*)(const u8*)&D_0021BB58, 0xC, 0xB, 0xE50, {
    (Fn_Table)func_0018A388, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001C74E8, (Fn_Table)func_001C7520,
    (Fn_Table)func_00126F78, (Fn_Table)func_001C7188, (Fn_Table)func_0018A3B8, 0,
    0, (Fn_Table)func_0018B340, (Fn_Table)func_001BB210, (Fn_Table)func_001C71E0,
    (Fn_Table)func_0018A3F0, (Fn_Table)func_0018ACD0, (Fn_Table)func_001C5438, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001C75B0, (Fn_Table)func_001B9690, (Fn_Table)func_001C4FA0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001C5DB8,
    (Fn_Table)func_00125C90, (Fn_Table)func_0018A628, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001C96D8, (Fn_Table)func_0018ACF0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001C4FF8, (Fn_Table)func_001BC760, (Fn_Table)func_001C4F08, (Fn_Table)func_001BC978,
    (Fn_Table)func_001C7468, (Fn_Table)func_00187F40, (Fn_Table)func_001CAD98, (Fn_Table)func_001B8B90,
    (Fn_Table)func_001CAC30, (Fn_Table)func_001C53E0, (Fn_Table)func_001CACB0, (Fn_Table)func_001C57C8,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_00192380, (Fn_Table)func_001BA5B0, (Fn_Table)func_001CB3C0,
    (Fn_Table)func_001922E8, 0, (Fn_Table)func_00192410, (Fn_Table)func_001C9A48,
    (Fn_Table)func_001C9990, (Fn_Table)func_00192490, (Fn_Table)func_001924C8, (Fn_Table)func_001925C0,
    (Fn_Table)func_00192C58, (Fn_Table)func_00192A28, (Fn_Table)func_00192A38, (Fn_Table)func_001930B0,
    (Fn_Table)func_001C53B0, (Fn_Table)func_001C4F00, (Fn_Table)func_001C5248, (Fn_Table)func_0018AAE0,
    (Fn_Table)func_001CA460, (Fn_Table)func_0018ABF0, (Fn_Table)func_0018AE38, (Fn_Table)func_0018B2E8,
    (Fn_Table)func_0018AB88, (Fn_Table)func_0018A9A8, (Fn_Table)func_0018AD88, (Fn_Table)func_001C8590,
    (Fn_Table)func_001C9CF8, (Fn_Table)func_001C9AF8, (Fn_Table)func_001CAA08, 0,
} };
extern const ClassDesc_217418<100> D_0021EA68 = { (const void*)(const u8*)&D_0021BB58, 0xD, 0xB, 0xC30, {
    (Fn_Table)func_001C6F48, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001C74E8, (Fn_Table)func_001C7520,
    (Fn_Table)func_00126F78, (Fn_Table)func_001C7188, (Fn_Table)func_001C7140, 0,
    0, (Fn_Table)func_001C9DE0, (Fn_Table)func_001BB210, (Fn_Table)func_001C71E0,
    (Fn_Table)func_001A98F8, (Fn_Table)func_001A9A40, (Fn_Table)func_001C5438, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001C75B0, (Fn_Table)func_001B9690, (Fn_Table)func_001C4FA0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001C5DB8,
    (Fn_Table)func_00125C90, (Fn_Table)func_001CA5E0, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001A9AE8, (Fn_Table)func_001A9A98, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001C4FF8, (Fn_Table)func_001BC760, (Fn_Table)func_001C4F08, (Fn_Table)func_001BC978,
    (Fn_Table)func_001C7468, (Fn_Table)func_00187F40, (Fn_Table)func_001CAD98, (Fn_Table)func_001B8B90,
    (Fn_Table)func_001CAC30, (Fn_Table)func_001C53E0, (Fn_Table)func_001CACB0, (Fn_Table)func_001C57C8,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_00192380, (Fn_Table)func_001BA5B0, (Fn_Table)func_001CB3C0,
    (Fn_Table)func_001922E8, 0, (Fn_Table)func_00192410, (Fn_Table)func_001C9A48,
    (Fn_Table)func_001C9990, (Fn_Table)func_00192490, (Fn_Table)func_001924C8, (Fn_Table)func_001925C0,
    (Fn_Table)func_00192C58, (Fn_Table)func_00192A28, (Fn_Table)func_00192A38, (Fn_Table)func_001930B0,
    (Fn_Table)func_001C53B0, (Fn_Table)func_001C4F00, (Fn_Table)func_001C5248, (Fn_Table)func_001A9928,
    (Fn_Table)func_001CA460, (Fn_Table)func_001C8010, (Fn_Table)func_001A99B8, (Fn_Table)func_001C9008,
    (Fn_Table)func_001A99F8, (Fn_Table)func_001CA468, (Fn_Table)func_001A9960, (Fn_Table)func_001C8590,
    (Fn_Table)func_001C9CF8, (Fn_Table)func_001C9AF8, (Fn_Table)func_001CAA08, 0,
} };
extern const ClassDesc_217418<84> D_0021EC08 = { (const void*)(const u8*)&D_00217C30, 0x1C, 0xB, 0x690, {
    (Fn_Table)func_001EB460, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_00192820, (Fn_Table)func_00192850,
    (Fn_Table)func_00126F78, (Fn_Table)func_001921E8, (Fn_Table)func_001EB518, 0,
    0, (Fn_Table)func_00192230, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_001EB598, (Fn_Table)func_00192B58, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001B9338, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_001EBD10, (Fn_Table)func_001EBDD0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001B93D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001BC320, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_001B8A08, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_00192380, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
    (Fn_Table)func_001EB608, (Fn_Table)func_001EB748, (Fn_Table)func_00192410, (Fn_Table)func_001EBC88,
    (Fn_Table)func_001EBD08, (Fn_Table)func_00192490, (Fn_Table)func_001924C8, (Fn_Table)func_001925C0,
    (Fn_Table)func_00192C58, (Fn_Table)func_00192A28, (Fn_Table)func_00192A38, (Fn_Table)func_001930B0,
} };
extern const ClassDesc_217418<100> D_0021ED68 = { (const void*)(const u8*)&D_0021BB58, 0x13, 0xB, 0xCA0, {
    (Fn_Table)func_001EBEB0, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001EC0B8, (Fn_Table)func_001EC098,
    (Fn_Table)func_00126F78, (Fn_Table)func_001C7188, (Fn_Table)func_001EBF40, 0,
    0, (Fn_Table)func_001EC828, (Fn_Table)func_001BB210, (Fn_Table)func_001C71E0,
    (Fn_Table)func_001EBFB0, (Fn_Table)func_001ECBC8, (Fn_Table)func_001C5438, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001C75B0, (Fn_Table)func_001B9690, (Fn_Table)func_001C4FA0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001C5DB8,
    (Fn_Table)func_001EC380, (Fn_Table)func_001EC3D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001C96D8, (Fn_Table)func_001ECDF8, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001C4FF8, (Fn_Table)func_001BC760, (Fn_Table)func_001C4F08, (Fn_Table)func_001BC978,
    (Fn_Table)func_001C7468, (Fn_Table)func_00187F40, (Fn_Table)func_001CAD98, (Fn_Table)func_001B8B90,
    (Fn_Table)func_001CAC30, (Fn_Table)func_001C53E0, (Fn_Table)func_001CACB0, (Fn_Table)func_001C57C8,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_00192380, (Fn_Table)func_001BA5B0, (Fn_Table)func_001CB3C0,
    (Fn_Table)func_001922E8, 0, (Fn_Table)func_00192410, (Fn_Table)func_001C9A48,
    (Fn_Table)func_001C9990, (Fn_Table)func_00192490, (Fn_Table)func_001924C8, (Fn_Table)func_001925C0,
    (Fn_Table)func_00192C58, (Fn_Table)func_00192A28, (Fn_Table)func_00192A38, (Fn_Table)func_001930B0,
    (Fn_Table)func_001C53B0, (Fn_Table)func_001C4F00, (Fn_Table)func_001C5248, (Fn_Table)func_001EC188,
    (Fn_Table)func_001CA460, (Fn_Table)func_001C8010, (Fn_Table)func_001ECF10, (Fn_Table)func_001EC478,
    (Fn_Table)func_001EC570, (Fn_Table)func_001EC0D8, (Fn_Table)func_001ECE98, (Fn_Table)func_001C8590,
    (Fn_Table)func_001C9CF8, (Fn_Table)func_001C9AF8, (Fn_Table)func_001CAA08, 0,
} };
extern const ClassDesc_217418<28> D_0021EF08 = { (const void*)(const u8*)&D_00217418, 0x90, 0x0, 0x48, {
    (Fn_Table)func_001ED168, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00182D00, (Fn_Table)func_00182E88, (Fn_Table)func_00182D48, (Fn_Table)func_00182ED0,
    (Fn_Table)func_001830B0, (Fn_Table)func_001830D8, (Fn_Table)func_001833D0, 0,
    0, 0, (Fn_Table)func_00183350, 0,
    (Fn_Table)func_001ED198, 0, 0, 0,
    0, (Fn_Table)func_00182F78, 0, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, 0,
} };
extern const ClassDesc_217418<48> D_0021EF88 = { (const void*)(const u8*)&D_00217498, 0x64, 0x1, 0x340, {
    (Fn_Table)func_0016DD10, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001240F8, (Fn_Table)func_001243E0,
    (Fn_Table)func_00126F78, (Fn_Table)func_00127048, (Fn_Table)func_0016DD90, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_00183350, (Fn_Table)func_001249A8,
    (Fn_Table)func_0016DDE8, (Fn_Table)func_00124FC0, (Fn_Table)func_00125108, (Fn_Table)func_00125138,
    (Fn_Table)func_0015FBB8, (Fn_Table)func_001245A8, (Fn_Table)func_00124868, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_00125440,
    (Fn_Table)func_00125438, (Fn_Table)func_001273F0, (Fn_Table)func_00127478, (Fn_Table)func_001276C0,
    (Fn_Table)func_001274F8, (Fn_Table)func_00127590, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001261C0, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_0012B2E8, 0, 0,
} };
extern const ClassDesc_217418<72> D_0021F058 = { (const void*)(const u8*)&D_00218F80, 0x2A, 0x3, 0x7C0, {
    (Fn_Table)func_0016DF30, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001B7A98, (Fn_Table)func_001B7B78,
    (Fn_Table)func_00126F78, (Fn_Table)func_00140200, (Fn_Table)func_00140100, 0,
    0, (Fn_Table)func_0016DFE0, (Fn_Table)func_001BB210, (Fn_Table)func_0016DF68,
    (Fn_Table)func_00140140, (Fn_Table)func_00140258, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001B9338, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001B93D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001BC320, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_001B8A08, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_001B9F30, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
} };
extern const ClassDesc_217418<72> D_0021F188 = { (const void*)(const u8*)&D_00217568, 0x47, 0x3, 0x5E0, {
    (Fn_Table)func_0016CE00, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001B7A98, (Fn_Table)func_001B7B78,
    (Fn_Table)func_00126F78, (Fn_Table)func_001BA130, (Fn_Table)func_0016CE80, 0,
    0, (Fn_Table)func_0016DA00, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_0016CF70, (Fn_Table)func_0016D128, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_0016D0C0, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001B93D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001BC320, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_001B8A08, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_001B9F30, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
} };
extern const ClassDesc_217418<28> D_0021F2B8 = { (const void*)(const u8*)&D_002177C0, 0x81, 0x0, 0x60, {
    (Fn_Table)func_001C10A8, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00182D00, (Fn_Table)func_00182E88, (Fn_Table)func_001C10D8, (Fn_Table)func_001C1110,
    (Fn_Table)func_001830B0, (Fn_Table)func_001C1148, (Fn_Table)func_00192068, 0,
    0, 0, (Fn_Table)func_00183350, 0,
    (Fn_Table)func_00182C58, 0, 0, 0,
    0, (Fn_Table)func_001920E0, (Fn_Table)func_00192128, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, 0,
} };
extern const ClassDesc_217418<28> D_0021F338 = { (const void*)(const u8*)&D_00217740, 0x71, 0x0, 0x5C, {
    (Fn_Table)func_0019AF00, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00182D00, (Fn_Table)func_00182E88, (Fn_Table)func_0019AF38, (Fn_Table)func_0019AF70,
    (Fn_Table)func_001830B0, (Fn_Table)func_0019AFF0, (Fn_Table)func_001B2840, 0,
    0, 0, (Fn_Table)func_00183350, 0,
    (Fn_Table)func_0019AFA8, 0, 0, 0,
    0, (Fn_Table)func_001B28A8, 0, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, 0,
} };
extern const ClassDesc_217418<28> D_0021F3B8 = { (const void*)(const u8*)&D_00217740, 0x72, 0x0, 0x40, {
    (Fn_Table)func_00182C18, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00182D00, (Fn_Table)func_00182E88, (Fn_Table)func_00180EB0, (Fn_Table)func_00180EE8,
    (Fn_Table)func_001830B0, (Fn_Table)func_00180F20, (Fn_Table)func_001B2840, 0,
    0, 0, (Fn_Table)func_00183350, 0,
    (Fn_Table)func_00182C58, 0, 0, 0,
    0, (Fn_Table)func_001B28A8, 0, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, 0,
} };
extern const ClassDesc_217418<28> D_0021F438 = { (const void*)(const u8*)&D_00217418, 0x8D, 0x0, 0x8F0, {
    (Fn_Table)func_001F2758, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00182D00, (Fn_Table)func_00182E88, (Fn_Table)func_00182D48, (Fn_Table)func_00182ED0,
    (Fn_Table)func_001830B0, (Fn_Table)func_001830D8, (Fn_Table)func_001833D0, 0,
    0, 0, (Fn_Table)func_00183350, 0,
    (Fn_Table)func_00182C58, 0, 0, 0,
    0, (Fn_Table)func_00182F78, 0, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, 0,
} };
extern const ClassDesc_217418<88> D_0021F4B8 = { (const void*)(const u8*)&D_0021A838, 0x14, 0xB, 0x760, {
    (Fn_Table)func_001DE798, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_00192820, (Fn_Table)func_00192850,
    (Fn_Table)func_00126F78, (Fn_Table)func_001921E8, (Fn_Table)func_001BAC30, 0,
    0, (Fn_Table)func_001DFB08, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_001DE808, (Fn_Table)func_001DE910, (Fn_Table)func_001C5438, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001C5118, (Fn_Table)func_001B9690, (Fn_Table)func_001C4FA0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001C5DB8,
    (Fn_Table)func_001DF2C8, (Fn_Table)func_001C49C8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001BC320, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001DF520, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001C4FF8, (Fn_Table)func_001BC760, (Fn_Table)func_001C4F08, (Fn_Table)func_001BC978,
    (Fn_Table)func_001B8A08, (Fn_Table)func_00187F40, (Fn_Table)func_001C5BF0, (Fn_Table)func_001B8B90,
    (Fn_Table)func_001DFA40, (Fn_Table)func_001C53E0, (Fn_Table)func_001C5388, (Fn_Table)func_001DFA10,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_00192380, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
    (Fn_Table)func_001DF290, (Fn_Table)func_001DEBE8, (Fn_Table)func_00192410, (Fn_Table)func_001DF5A0,
    (Fn_Table)func_001DF700, (Fn_Table)func_001DFBD0, (Fn_Table)func_001924C8, (Fn_Table)func_001925C0,
    (Fn_Table)func_001DEBB8, (Fn_Table)func_00192A28, (Fn_Table)func_00192A38, (Fn_Table)func_001930B0,
    (Fn_Table)func_001C53B0, (Fn_Table)func_001C4F00, (Fn_Table)func_001C5248, 0,
} };
extern const ClassDesc_217418<84> D_0021F628 = { (const void*)(const u8*)&D_00217C30, 0x16, 0xB, 0x660, {
    (Fn_Table)func_001E5378, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_00192820, (Fn_Table)func_00192850,
    (Fn_Table)func_00126F78, (Fn_Table)func_001921E8, (Fn_Table)func_001BAC30, 0,
    0, (Fn_Table)func_001E5CE8, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_001E5428, (Fn_Table)func_001E55D0, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001B9338, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001B93D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001BC320, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_001E5DA8, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_00192380, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
    (Fn_Table)func_001E5750, (Fn_Table)func_001E56A0, (Fn_Table)func_00192410, (Fn_Table)func_00192450,
    (Fn_Table)func_00192488, (Fn_Table)func_00192490, (Fn_Table)func_001E5E08, (Fn_Table)func_001925C0,
    (Fn_Table)func_00192C58, (Fn_Table)func_001E5E50, (Fn_Table)func_00192A38, (Fn_Table)func_001E5E60,
} };
extern const ClassDesc_217418<100> D_0021F788 = { (const void*)(const u8*)&D_0021BB58, 0xE, 0xB, 0xC50, {
    (Fn_Table)func_0018FEF8, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001C74E8, (Fn_Table)func_001C7520,
    (Fn_Table)func_00126F78, (Fn_Table)func_001C7188, (Fn_Table)func_001C7140, 0,
    0, (Fn_Table)func_00190770, (Fn_Table)func_001BB210, (Fn_Table)func_001C71E0,
    (Fn_Table)func_0018FF28, (Fn_Table)func_001C7CB8, (Fn_Table)func_001C5438, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001C75B0, (Fn_Table)func_001B9690, (Fn_Table)func_001C4FA0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001C5DB8,
    (Fn_Table)func_00125C90, (Fn_Table)func_001CA5E0, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001904E0, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001C4FF8, (Fn_Table)func_001BC760, (Fn_Table)func_001C4F08, (Fn_Table)func_001BC978,
    (Fn_Table)func_001C7468, (Fn_Table)func_00187F40, (Fn_Table)func_001CAD98, (Fn_Table)func_001B8B90,
    (Fn_Table)func_001CAC30, (Fn_Table)func_001C53E0, (Fn_Table)func_001CACB0, (Fn_Table)func_001C57C8,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_00192380, (Fn_Table)func_001BA5B0, (Fn_Table)func_001CB3C0,
    (Fn_Table)func_001922E8, 0, (Fn_Table)func_00192410, (Fn_Table)func_001903F0,
    (Fn_Table)func_00190450, (Fn_Table)func_00190740, (Fn_Table)func_001906F8, (Fn_Table)func_001925C0,
    (Fn_Table)func_00192C58, (Fn_Table)func_00192A28, (Fn_Table)func_00192A38, (Fn_Table)func_001930B0,
    (Fn_Table)func_001C53B0, (Fn_Table)func_001C4F00, (Fn_Table)func_001C5248, (Fn_Table)func_00190570,
    (Fn_Table)func_001CA460, (Fn_Table)func_001C8010, (Fn_Table)func_00190258, (Fn_Table)func_001900A0,
    (Fn_Table)func_0018FFB0, (Fn_Table)func_00190658, (Fn_Table)func_00190128, (Fn_Table)func_001C8590,
    (Fn_Table)func_001C9CF8, (Fn_Table)func_001C9AF8, (Fn_Table)func_001CAA08, 0,
} };
extern const ClassDesc_217418<84> D_0021F928 = { (const void*)(const u8*)&D_00217C30, 0x18, 0xB, 0x6C0, {
    (Fn_Table)func_00196938, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_00192820, (Fn_Table)func_00192850,
    (Fn_Table)func_00126F78, (Fn_Table)func_001921E8, (Fn_Table)func_001969C0, 0,
    0, (Fn_Table)func_00197F10, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_001969F8, (Fn_Table)func_00196EB0, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_00196B78, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001B93D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001BC320, (Fn_Table)func_00197788, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_001B8A08, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    (Fn_Table)func_00197A68, 0, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_00192380, (Fn_Table)func_00197A88, (Fn_Table)func_001BBC30,
    (Fn_Table)func_001974D8, (Fn_Table)func_001974F8, (Fn_Table)func_00192410, (Fn_Table)func_00192450,
    (Fn_Table)func_00192488, (Fn_Table)func_00192490, (Fn_Table)func_001924C8, (Fn_Table)func_001925C0,
    (Fn_Table)func_00192C58, (Fn_Table)func_00192A28, (Fn_Table)func_00192A38, (Fn_Table)func_001930B0,
} };
extern const ClassDesc_217418<100> D_0021FA88 = { (const void*)(const u8*)&D_0021BB58, 0xF, 0xB, 0xC20, {
    (Fn_Table)func_001C6F48, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001C74E8, (Fn_Table)func_001C7520,
    (Fn_Table)func_00126F78, (Fn_Table)func_001C7188, (Fn_Table)func_001C7140, 0,
    0, (Fn_Table)func_001986E8, (Fn_Table)func_001BB210, (Fn_Table)func_001C71E0,
    (Fn_Table)func_00198090, (Fn_Table)func_00198760, (Fn_Table)func_001C5438, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001980B0, (Fn_Table)func_001B9690, (Fn_Table)func_001C4FA0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001C5DB8,
    (Fn_Table)func_00125C90, (Fn_Table)func_001CA5E0, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001C96D8, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001C4FF8, (Fn_Table)func_001BC760, (Fn_Table)func_001C4F08, (Fn_Table)func_001BC978,
    (Fn_Table)func_001C7468, (Fn_Table)func_00187F40, (Fn_Table)func_001CAD98, (Fn_Table)func_001B8B90,
    (Fn_Table)func_001CAC30, (Fn_Table)func_001C53E0, (Fn_Table)func_001CACB0, (Fn_Table)func_001C57C8,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_00192380, (Fn_Table)func_001BA5B0, (Fn_Table)func_001CB3C0,
    (Fn_Table)func_001922E8, 0, (Fn_Table)func_00192410, (Fn_Table)func_001C9A48,
    (Fn_Table)func_001C9990, (Fn_Table)func_00192490, (Fn_Table)func_001924C8, (Fn_Table)func_001925C0,
    (Fn_Table)func_00192C58, (Fn_Table)func_00192A28, (Fn_Table)func_00192A38, (Fn_Table)func_001930B0,
    (Fn_Table)func_001C53B0, (Fn_Table)func_001C4F00, (Fn_Table)func_001C5248, (Fn_Table)func_00198860,
    (Fn_Table)func_001CA460, (Fn_Table)func_001982A0, (Fn_Table)func_00198570, (Fn_Table)func_001984B8,
    (Fn_Table)func_00198530, (Fn_Table)func_00198858, (Fn_Table)func_00198318, (Fn_Table)func_001C8590,
    (Fn_Table)func_001C9CF8, (Fn_Table)func_001C9AF8, (Fn_Table)func_001CAA08, 0,
} };
extern const ClassDesc_217418<72> D_0021FC28 = { (const void*)(const u8*)&D_00217568, 0x48, 0x3, 0x560, {
    (Fn_Table)func_001B7968, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001B7A98, (Fn_Table)func_001B7B78,
    (Fn_Table)func_00126F78, (Fn_Table)func_001BA130, (Fn_Table)func_001BAC30, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_00198920, (Fn_Table)func_001B93F8, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001B9338, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001B93D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001BC320, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_001B8A08, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_001B9F30, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
} };
extern const ClassDesc_217418<72> D_0021FD58 = { (const void*)(const u8*)&D_00217568, 0x49, 0x3, 0x570, {
    (Fn_Table)func_0018F988, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001B7A98, (Fn_Table)func_001B7B78,
    (Fn_Table)func_00126F78, (Fn_Table)func_001BA130, (Fn_Table)func_001BAC30, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_00124A48, (Fn_Table)func_001B93F8, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001B9338, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001B93D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001BC320, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_001B8A08, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_001B9F30, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
} };
extern const ClassDesc_217418<100> D_0021FE88 = { (const void*)(const u8*)&D_0021BB58, 0x10, 0xB, 0xC20, {
    (Fn_Table)func_001C6F48, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_0014B550, (Fn_Table)func_0014B588,
    (Fn_Table)func_00126F78, (Fn_Table)func_0014B5C0, (Fn_Table)func_001C7140, 0,
    0, (Fn_Table)func_001C9DE0, (Fn_Table)func_001BB210, (Fn_Table)func_001C71E0,
    (Fn_Table)func_001C72A0, (Fn_Table)func_001C7CB8, (Fn_Table)func_001C5438, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001C75B0, (Fn_Table)func_001B9690, (Fn_Table)func_001C4FA0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001C5DB8,
    (Fn_Table)func_00125C90, (Fn_Table)func_001CA5E0, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001C96D8, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001C4FF8, (Fn_Table)func_001BC760, (Fn_Table)func_001C4F08, (Fn_Table)func_001BC978,
    (Fn_Table)func_001C7468, (Fn_Table)func_00187F40, (Fn_Table)func_001CAD98, (Fn_Table)func_001B8B90,
    (Fn_Table)func_001CAC30, (Fn_Table)func_001C53E0, (Fn_Table)func_001CACB0, (Fn_Table)func_001C57C8,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_00192380, (Fn_Table)func_001BA5B0, (Fn_Table)func_001CB3C0,
    (Fn_Table)func_001922E8, 0, (Fn_Table)func_00192410, (Fn_Table)func_001C9A48,
    (Fn_Table)func_001C9990, (Fn_Table)func_00192490, (Fn_Table)func_001924C8, (Fn_Table)func_001925C0,
    (Fn_Table)func_00192C58, (Fn_Table)func_00192A28, (Fn_Table)func_00192A38, (Fn_Table)func_001930B0,
    (Fn_Table)func_001C53B0, (Fn_Table)func_001C4F00, (Fn_Table)func_001C5248, (Fn_Table)func_001CB3C8,
    (Fn_Table)func_001CA460, (Fn_Table)func_001C8010, (Fn_Table)func_001C8E28, (Fn_Table)func_001C9008,
    (Fn_Table)func_001C91C8, (Fn_Table)func_001CA468, (Fn_Table)func_001C8C08, (Fn_Table)func_001C8590,
    (Fn_Table)func_001C9CF8, (Fn_Table)func_001C9AF8, (Fn_Table)func_001CAA08, 0,
} };
extern const ClassDesc_217418<100> D_00220028 = { (const void*)(const u8*)&D_0021FE88, 0x11, 0xB, 0xC30, {
    (Fn_Table)func_0014B608, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_0014B550, (Fn_Table)func_0014B588,
    (Fn_Table)func_00126F78, (Fn_Table)func_0014B5C0, (Fn_Table)func_001C7140, 0,
    0, (Fn_Table)func_001C9DE0, (Fn_Table)func_001BB210, (Fn_Table)func_001C71E0,
    (Fn_Table)func_0014B640, (Fn_Table)func_001C7CB8, (Fn_Table)func_001C5438, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001C75B0, (Fn_Table)func_001B9690, (Fn_Table)func_001C4FA0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001C5DB8,
    (Fn_Table)func_00125C90, (Fn_Table)func_001CA5E0, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_0014BCE8, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001C4FF8, (Fn_Table)func_001BC760, (Fn_Table)func_001C4F08, (Fn_Table)func_001BC978,
    (Fn_Table)func_001C7468, (Fn_Table)func_00187F40, (Fn_Table)func_001CAD98, (Fn_Table)func_001B8B90,
    (Fn_Table)func_001CAC30, (Fn_Table)func_001C53E0, (Fn_Table)func_001CACB0, (Fn_Table)func_001C57C8,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_00192380, (Fn_Table)func_001BA5B0, (Fn_Table)func_001CB3C0,
    (Fn_Table)func_001922E8, 0, (Fn_Table)func_00192410, (Fn_Table)func_001C9A48,
    (Fn_Table)func_001C9990, (Fn_Table)func_00192490, (Fn_Table)func_001924C8, (Fn_Table)func_001925C0,
    (Fn_Table)func_00192C58, (Fn_Table)func_00192A28, (Fn_Table)func_00192A38, (Fn_Table)func_001930B0,
    (Fn_Table)func_001C53B0, (Fn_Table)func_001C4F00, (Fn_Table)func_001C5248, (Fn_Table)func_0014BB08,
    (Fn_Table)func_001CA460, (Fn_Table)func_001C8010, (Fn_Table)func_001C8E28, (Fn_Table)func_001C9008,
    (Fn_Table)func_0014BD38, (Fn_Table)func_001CA468, (Fn_Table)func_0014B6A8, (Fn_Table)func_001C8590,
    (Fn_Table)func_001C9CF8, (Fn_Table)func_001C9AF8, (Fn_Table)func_001CAA08, 0,
} };
extern const ClassDesc_217418<100> D_002201C8 = { (const void*)(const u8*)&D_0021FE88, 0x12, 0xB, 0xC30, {
    (Fn_Table)func_001C6F48, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_0014B550, (Fn_Table)func_0014B588,
    (Fn_Table)func_00126F78, (Fn_Table)func_0014B5C0, (Fn_Table)func_001C7140, 0,
    0, (Fn_Table)func_001C9DE0, (Fn_Table)func_001BB210, (Fn_Table)func_001C71E0,
    (Fn_Table)func_001C72A0, (Fn_Table)func_001C7CB8, (Fn_Table)func_001C5438, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001C75B0, (Fn_Table)func_001B9690, (Fn_Table)func_001C4FA0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001C5DB8,
    (Fn_Table)func_00125C90, (Fn_Table)func_001CA5E0, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_0014BEF8, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001C4FF8, (Fn_Table)func_001BC760, (Fn_Table)func_001C4F08, (Fn_Table)func_001BC978,
    (Fn_Table)func_001C7468, (Fn_Table)func_00187F40, (Fn_Table)func_001CAD98, (Fn_Table)func_001B8B90,
    (Fn_Table)func_001CAC30, (Fn_Table)func_001C53E0, (Fn_Table)func_001CACB0, (Fn_Table)func_001C57C8,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_00192380, (Fn_Table)func_001BA5B0, (Fn_Table)func_001CB3C0,
    (Fn_Table)func_001922E8, 0, (Fn_Table)func_00192410, (Fn_Table)func_001C9A48,
    (Fn_Table)func_001C9990, (Fn_Table)func_00192490, (Fn_Table)func_001924C8, (Fn_Table)func_001925C0,
    (Fn_Table)func_00192C58, (Fn_Table)func_00192A28, (Fn_Table)func_00192A38, (Fn_Table)func_001930B0,
    (Fn_Table)func_001C53B0, (Fn_Table)func_001C4F00, (Fn_Table)func_001C5248, (Fn_Table)func_0014BEA8,
    (Fn_Table)func_001CA460, (Fn_Table)func_0014BDC8, (Fn_Table)func_001C8E28, (Fn_Table)func_001C9008,
    (Fn_Table)func_0014BF88, (Fn_Table)func_001CA468, (Fn_Table)func_001C8C08, (Fn_Table)func_001C8590,
    (Fn_Table)func_001C9CF8, (Fn_Table)func_001C9AF8, (Fn_Table)func_001CAA08, 0,
} };
extern const ClassDesc_217418<48> D_00220368 = { (const void*)(const u8*)&D_00217498, 0x68, 0x1, 0x6A0, {
    (Fn_Table)func_0014C018, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001240F8, (Fn_Table)func_001243E0,
    (Fn_Table)func_00126F78, (Fn_Table)func_00127048, (Fn_Table)func_001289C0, 0,
    0, (Fn_Table)func_0014CF30, (Fn_Table)func_00183350, (Fn_Table)func_001249A8,
    (Fn_Table)func_0014C138, (Fn_Table)func_0014C6E0, (Fn_Table)func_00125108, (Fn_Table)func_00125138,
    (Fn_Table)func_0015FBB8, (Fn_Table)func_001245A8, (Fn_Table)func_00124868, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_00125440,
    (Fn_Table)func_00125438, (Fn_Table)func_001273F0, (Fn_Table)func_00127478, (Fn_Table)func_001276C0,
    (Fn_Table)func_001274F8, (Fn_Table)func_00127590, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001261C0, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_0012B2E8, (Fn_Table)func_0014C788, 0,
} };
extern const ClassDesc_217418<84> D_00220438 = { (const void*)(const u8*)&D_00217C30, 0x19, 0xB, 0xBB0, {
    (Fn_Table)func_001D73A8, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_00192820, (Fn_Table)func_00192850,
    (Fn_Table)func_00126F78, (Fn_Table)func_001921E8, (Fn_Table)func_001BAC30, 0,
    0, (Fn_Table)func_001DAF08, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_001D7440, (Fn_Table)func_001D9C98, (Fn_Table)func_001DAE18, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001D7778, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001DAA18, (Fn_Table)func_00126270, (Fn_Table)func_001DA7E0,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001BC320, (Fn_Table)func_001DA170, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001DAC20, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_001B8A08, (Fn_Table)func_00187F40, (Fn_Table)func_001DA320, (Fn_Table)func_001B8B90,
    (Fn_Table)func_001DA6E0, 0, 0, 0,
    (Fn_Table)func_001DA310, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_001DAE48, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
    (Fn_Table)func_001DAE68, (Fn_Table)func_001D9D78, (Fn_Table)func_00192410, (Fn_Table)func_00192450,
    (Fn_Table)func_00192488, (Fn_Table)func_00192490, (Fn_Table)func_001DACB0, (Fn_Table)func_001925C0,
    (Fn_Table)func_00192C58, (Fn_Table)func_00192A28, (Fn_Table)func_00192A38, (Fn_Table)func_001930B0,
} };
extern const ClassDesc_217418<84> D_00220598 = { (const void*)(const u8*)&D_00217C30, 0x1B, 0xB, 0x710, {
    (Fn_Table)func_001793C0, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_00192820, (Fn_Table)func_00192850,
    (Fn_Table)func_00126F78, (Fn_Table)func_001921E8, (Fn_Table)func_001BAC30, 0,
    0, (Fn_Table)func_0017AB58, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_001793F0, (Fn_Table)func_001796D0, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_00179690,
    (Fn_Table)func_00179590, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_0017A788, (Fn_Table)func_001B93D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001BC320, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_001B8A08, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_00192380, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
    (Fn_Table)func_0017A700, (Fn_Table)func_00179A68, (Fn_Table)func_00192410, (Fn_Table)func_0017A9E0,
    (Fn_Table)func_0017AA40, (Fn_Table)func_0017ABD8, (Fn_Table)func_001924C8, (Fn_Table)func_001925C0,
    (Fn_Table)func_0017A6D0, (Fn_Table)func_00192A28, (Fn_Table)func_00192A38, (Fn_Table)func_001930B0,
} };
extern const ClassDesc_217418<72> D_002206F8 = { (const void*)(const u8*)&D_00217568, 0x4A, 0x3, 0x620, {
    (Fn_Table)func_0017ADD0, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001B7A98, (Fn_Table)func_001B7B78,
    (Fn_Table)func_00126F78, (Fn_Table)func_001BA130, (Fn_Table)func_001BAC30, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_0017AE00, (Fn_Table)func_0017AF38, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001B9338, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001B93D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_0017B3A8, (Fn_Table)func_0017B308, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_001B8A08, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_001B9F30, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
} };
extern const ClassDesc_217418<72> D_00220828 = { (const void*)(const u8*)&D_00217568, 0x4B, 0x3, 0x570, {
    (Fn_Table)func_0017B5D0, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001B7A98, (Fn_Table)func_001B7B78,
    (Fn_Table)func_00126F78, (Fn_Table)func_001BA130, (Fn_Table)func_001BAC30, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_0017B610, (Fn_Table)func_0017B648, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001B9338, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001B93D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_0017B7A8, (Fn_Table)func_0017B710, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_001B8A08, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_001B9F30, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
} };
extern const ClassDesc_217418<74> D_00220958 = { (const void*)(const u8*)&D_00218BD8, 0x24, 0x13, 0x6F0, {
    (Fn_Table)func_00182470, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001B7A98, (Fn_Table)func_001B7B78,
    (Fn_Table)func_00126F78, (Fn_Table)func_0013CDE8, (Fn_Table)func_0013CD80, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_001824D8, (Fn_Table)func_00182548, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_00182748,
    (Fn_Table)func_001B9338, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001B93D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_0013D0B0, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_001B8A08, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_001B9F30, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
    (Fn_Table)func_0013D278, 0,
} };
extern const ClassDesc_217418<84> D_00220A90 = { (const void*)(const u8*)&D_00220438, 0x1A, 0xB, 0xC10, {
    (Fn_Table)func_00180F68, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_00192820, (Fn_Table)func_00192850,
    (Fn_Table)func_00126F78, (Fn_Table)func_001921E8, (Fn_Table)func_001BAC30, 0,
    0, (Fn_Table)func_00181D28, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_00180F98, (Fn_Table)func_00181448, (Fn_Table)func_00181658, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001D7778, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00181818, (Fn_Table)func_001DAA18, (Fn_Table)func_00126270, (Fn_Table)func_001DA7E0,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001BC320, (Fn_Table)func_001DA170, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001DAC20, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_001B8A08, (Fn_Table)func_00187F40, (Fn_Table)func_001DA320, (Fn_Table)func_001B8B90,
    (Fn_Table)func_001DA6E0, 0, 0, (Fn_Table)func_00181D88,
    (Fn_Table)func_001DA310, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_00181A58, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
    (Fn_Table)func_00181780, (Fn_Table)func_00181078, (Fn_Table)func_00192410, (Fn_Table)func_00181A98,
    (Fn_Table)func_00181BC8, (Fn_Table)func_00181AE0, (Fn_Table)func_001DACB0, (Fn_Table)func_001925C0,
    (Fn_Table)func_00181AF0, (Fn_Table)func_00192A28, (Fn_Table)func_00192A38, (Fn_Table)func_001930B0,
} };
extern const ClassDesc_217418<28> D_00220C40 = { (const void*)(const u8*)&D_00217418, 0x91, 0x0, 0x60, {
    (Fn_Table)func_00182C18, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00182D00, (Fn_Table)func_00182E88, (Fn_Table)func_00182D48, (Fn_Table)func_00182ED0,
    (Fn_Table)func_001830B0, (Fn_Table)func_001830D8, (Fn_Table)func_001833D0, 0,
    0, 0, (Fn_Table)func_00183350, 0,
    (Fn_Table)func_00182C58, 0, 0, 0,
    0, (Fn_Table)func_00182F78, 0, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, 0,
} };
extern const ClassDesc_217418<84> D_00220CC0 = { (const void*)(const u8*)&D_00217C30, 0x1D, 0xB, 0x760, {
    (Fn_Table)func_001C3390, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_00192820, (Fn_Table)func_00192850,
    (Fn_Table)func_00126F78, (Fn_Table)func_001921E8, (Fn_Table)func_001BAC30, 0,
    0, (Fn_Table)func_00192230, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_001C33C8, (Fn_Table)func_001C34C8, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001C3B40, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001B93D8, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001BC320, (Fn_Table)func_001C3928, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_001B8A08, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    (Fn_Table)func_001C3C00, (Fn_Table)func_001C3C98, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_00192380, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
    (Fn_Table)func_001922E8, (Fn_Table)func_001C39A0, (Fn_Table)func_00192410, (Fn_Table)func_001C3D28,
    (Fn_Table)func_001C3D60, (Fn_Table)func_001C3E50, (Fn_Table)func_001924C8, (Fn_Table)func_001925C0,
    (Fn_Table)func_001C3E80, (Fn_Table)func_00192A28, (Fn_Table)func_00192A38, (Fn_Table)func_001930B0,
} };
extern const ClassDesc_217418<72> D_00220E20 = { (const void*)(const u8*)&D_00217568, 0x4, 0x3, 0x550, {
    (Fn_Table)func_001B7968, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001B7A98, (Fn_Table)func_001B7B78,
    (Fn_Table)func_00126F78, (Fn_Table)func_001BA130, (Fn_Table)func_001BAC30, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_001BB210, (Fn_Table)func_001249A8,
    (Fn_Table)func_00124A48, (Fn_Table)func_001B93F8, (Fn_Table)func_001B89B8, (Fn_Table)func_001B8960,
    (Fn_Table)func_0015FCD8, (Fn_Table)func_001B9B50, (Fn_Table)func_001B9C80, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_001BC088,
    (Fn_Table)func_001B9338, (Fn_Table)func_001B9690, (Fn_Table)func_001B97E0, (Fn_Table)func_001276C0,
    (Fn_Table)func_001B9940, (Fn_Table)func_001B99F0, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001B93D8, (Fn_Table)func_0018F9D8, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_001BC320, 0, (Fn_Table)func_001B7D00,
    (Fn_Table)func_001B7F78, (Fn_Table)func_001B8148, (Fn_Table)func_001B8540, (Fn_Table)func_001BAC28,
    (Fn_Table)func_001BC368, (Fn_Table)func_001BC760, (Fn_Table)func_001BC828, (Fn_Table)func_001BC978,
    (Fn_Table)func_001B8A08, (Fn_Table)func_00187F40, 0, (Fn_Table)func_001B8B90,
    0, 0, 0, 0,
    0, 0, 0, (Fn_Table)func_001B8A48,
    (Fn_Table)func_001B9680, (Fn_Table)func_001B9F30, (Fn_Table)func_001BA5B0, (Fn_Table)func_001BBC30,
} };
extern const ClassDesc_217418<48> D_00220F50 = { (const void*)(const u8*)&D_00217498, 0x66, 0x1, 0x340, {
    (Fn_Table)func_001C0F30, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001240F8, (Fn_Table)func_001243E0,
    (Fn_Table)func_00126F78, (Fn_Table)func_00127048, (Fn_Table)func_001289C0, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_00183350, (Fn_Table)func_001249A8,
    (Fn_Table)func_001C0FF0, (Fn_Table)func_00124FC0, (Fn_Table)func_00125108, (Fn_Table)func_00125138,
    (Fn_Table)func_0015FBB8, (Fn_Table)func_001245A8, (Fn_Table)func_00124868, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_00125440,
    (Fn_Table)func_00125438, (Fn_Table)func_001273F0, (Fn_Table)func_00127478, (Fn_Table)func_001276C0,
    (Fn_Table)func_001274F8, (Fn_Table)func_00127590, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001261C0, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_0012B2E8, 0, 0,
} };
extern const ClassDesc_217418<48> D_00221020 = { (const void*)(const u8*)&D_00217498, 0x67, 0x1, 0x570, {
    (Fn_Table)func_00123ED0, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001240F8, (Fn_Table)func_001243E0,
    (Fn_Table)func_00126F78, (Fn_Table)func_00127048, (Fn_Table)func_001289C0, 0,
    0, (Fn_Table)func_001F0F70, (Fn_Table)func_00183350, (Fn_Table)func_001F0758,
    (Fn_Table)func_001F0660, (Fn_Table)func_001F0AE0, (Fn_Table)func_00125108, (Fn_Table)func_00125138,
    (Fn_Table)func_0015FBB8, (Fn_Table)func_001245A8, (Fn_Table)func_00124868, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_00125440,
    (Fn_Table)func_00125438, (Fn_Table)func_001273F0, (Fn_Table)func_00127478, (Fn_Table)func_001276C0,
    (Fn_Table)func_001274F8, (Fn_Table)func_00127590, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_001F0EB8, (Fn_Table)func_001261C0, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_0012B2E8, 0, 0,
} };
extern const ClassDesc_217418<48> D_00221140 = { (const void*)(const u8*)&D_00217498, 0x6A, 0x1, 0x300, {
    (Fn_Table)func_00123ED0, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001240F8, (Fn_Table)func_001243E0,
    (Fn_Table)func_00126F78, (Fn_Table)func_00127048, (Fn_Table)func_001289C0, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_00183350, (Fn_Table)func_001249A8,
    (Fn_Table)func_0016AA18, (Fn_Table)func_00124FC0, (Fn_Table)func_00125108, (Fn_Table)func_00125138,
    (Fn_Table)func_0015FBB8, (Fn_Table)func_001245A8, (Fn_Table)func_00124868, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_00125440,
    (Fn_Table)func_00125438, (Fn_Table)func_001273F0, (Fn_Table)func_00127478, (Fn_Table)func_001276C0,
    (Fn_Table)func_001274F8, (Fn_Table)func_00127590, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001261C0, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_0012B2E8, 0, 0,
} };
extern const ClassDesc_217418<48> D_00221210 = { (const void*)(const u8*)&D_00217498, 0x69, 0x1, 0x350, {
    (Fn_Table)func_00123ED0, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001240F8, (Fn_Table)func_001243E0,
    (Fn_Table)func_00126F78, (Fn_Table)func_00127048, (Fn_Table)func_001289C0, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_00183350, (Fn_Table)func_001249A8,
    (Fn_Table)func_0016AED8, (Fn_Table)func_00124FC0, (Fn_Table)func_00125108, (Fn_Table)func_00125138,
    (Fn_Table)func_0015FBB8, (Fn_Table)func_001245A8, (Fn_Table)func_00124868, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_00125440,
    (Fn_Table)func_00125438, (Fn_Table)func_001273F0, (Fn_Table)func_00127478, (Fn_Table)func_001276C0,
    (Fn_Table)func_001274F8, (Fn_Table)func_00127590, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001261C0, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_0012B2E8, 0, 0,
} };
extern const ClassDesc_217418<48> D_002213D0 = { (const void*)(const u8*)&D_00217498, 0x6B, 0x1, 0x6E0, {
    (Fn_Table)func_0012B6B8, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00124050, (Fn_Table)func_00124338, (Fn_Table)func_001240F8, (Fn_Table)func_001243E0,
    (Fn_Table)func_00126F78, (Fn_Table)func_00127048, (Fn_Table)func_001289C0, 0,
    0, (Fn_Table)func_00127378, (Fn_Table)func_00183350, (Fn_Table)func_001249A8,
    (Fn_Table)func_00124A48, (Fn_Table)func_0012B760, (Fn_Table)func_00125108, (Fn_Table)func_00125138,
    (Fn_Table)func_0015FBB8, (Fn_Table)func_001245A8, (Fn_Table)func_00124868, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, (Fn_Table)func_00125440,
    (Fn_Table)func_00125438, (Fn_Table)func_001273F0, (Fn_Table)func_00127478, (Fn_Table)func_001276C0,
    (Fn_Table)func_001274F8, (Fn_Table)func_00127590, (Fn_Table)func_00122550, (Fn_Table)func_001225D0,
    (Fn_Table)func_00125C90, (Fn_Table)func_001261C0, (Fn_Table)func_00126270, (Fn_Table)func_001660E8,
    0, (Fn_Table)func_00128E88, (Fn_Table)func_00128FD0, (Fn_Table)func_00129780,
    (Fn_Table)func_001660A0, (Fn_Table)func_0012B2E8, 0, 0,
} };
extern const ClassDesc_217418<28> D_002214A0 = { (const void*)(const u8*)&D_00217418, 0x6C, 0x0, 0x2360, {
    (Fn_Table)func_001DB4C8, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00182D00, (Fn_Table)func_00182E88, (Fn_Table)func_00182D48, (Fn_Table)func_00182ED0,
    (Fn_Table)func_001830B0, (Fn_Table)func_001830D8, (Fn_Table)func_001DCEA0, 0,
    0, 0, (Fn_Table)func_00183350, 0,
    (Fn_Table)func_00182C58, (Fn_Table)func_001EA118, 0, 0,
    0, (Fn_Table)func_00182F78, 0, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, 0,
} };
extern const ClassDesc_217418<28> D_00221520 = { (const void*)(const u8*)&D_00217418, 0x6D, 0x0, 0x590, {
    (Fn_Table)func_00143648, (Fn_Table)func_0011EDA8, (Fn_Table)func_00182C80, (Fn_Table)func_00182D50,
    (Fn_Table)func_00182D00, (Fn_Table)func_00182E88, (Fn_Table)func_00182D48, (Fn_Table)func_00182ED0,
    (Fn_Table)func_001830B0, (Fn_Table)func_001830D8, (Fn_Table)func_001833D0, 0,
    0, 0, (Fn_Table)func_00183350, 0,
    (Fn_Table)func_00182C58, 0, 0, 0,
    0, (Fn_Table)func_00182F78, 0, (Fn_Table)func_001832F0,
    (Fn_Table)func_00183320, (Fn_Table)func_00183290, (Fn_Table)func_001832C0, 0,
} };

// The table of (a, b) pairs func_001BE4A8 (001BC000.cpp) and func_001C0070 (001C0000.cpp) index by id;
// the latter reads it from its second word (D_00245024).
struct Ent_1BFAF8 { s32 a; s32 b; };
extern const Ent_1BFAF8 D_00245020[771] = {
    { 0, 0 }, { 0, 1 }, { 0, 2 }, { 0, 3 }, { 0, 4 }, { 0, 5 }, { 0, 6 }, { 0, 7 },
    { 0, 8 }, { 0, 9 }, { 0, 10 }, { 0, 11 }, { 0, 12 }, { 0, 13 }, { 0, 14 }, { 0, 15 },
    { 0, 16 }, { 0, 17 }, { 0, 18 }, { 0, 19 }, { 0, 20 }, { 0, 21 }, { 0, 22 }, { 0, 23 },
    { 0, 24 }, { 0, 25 }, { 0, 26 }, { 0, 27 }, { 0, 28 }, { 0, 29 }, { 0, 30 }, { 0, 31 },
    { 0, 32 }, { 0, 33 }, { 0, 34 }, { 0, 35 }, { 0, 36 }, { 0, 37 }, { 0, 38 }, { 0, 39 },
    { 0, 40 }, { 0, 41 }, { 0, 42 }, { 0, 43 }, { 0, 44 }, { 0, 45 }, { 0, 46 }, { 0, 47 },
    { 0, 48 }, { 0, 49 }, { 0, 50 }, { 0, 51 }, { 0, 52 }, { 0, 53 }, { 0, 54 }, { 0, 55 },
    { 0, 56 }, { 0, 57 }, { 0, 58 }, { 0, 59 }, { 0, 60 }, { 0, 61 }, { 0, 62 }, { 0, 63 },
    { 0, 64 }, { 0, 65 }, { 0, 66 }, { 0, 67 }, { 0, 68 }, { 0, 69 }, { 0, 70 }, { 0, 71 },
    { 0, 72 }, { 0, 73 }, { 0, 74 }, { 0, 75 }, { 0, 76 }, { 0, 77 }, { 0, 78 }, { 0, 79 },
    { 0, 80 }, { 0, 81 }, { 0, 82 }, { 0, 83 }, { 0, 84 }, { 0, 85 }, { 0, 86 }, { 0, 87 },
    { 0, 88 }, { 0, 89 }, { 0, 90 }, { 0, 91 }, { 0, 92 }, { 0, 93 }, { 0, 94 }, { 0, 95 },
    { 0, 96 }, { 0, 97 }, { 0, 98 }, { 0, 99 }, { 0, 100 }, { 0, 101 }, { 0, 102 }, { 0, 103 },
    { 0, 104 }, { 0, 105 }, { 0, 106 }, { 0, 107 }, { 0, 108 }, { 0, 109 }, { 0, 110 }, { 0, 111 },
    { 0, 112 }, { 0, 113 }, { 0, 114 }, { 0, 115 }, { 0, 116 }, { 0, 117 }, { 0, 118 }, { 0, 119 },
    { 0, 120 }, { 0, 121 }, { 0, 122 }, { 0, 123 }, { 0, 124 }, { 0, 125 }, { 0, 126 }, { 0, 127 },
    { 0, 128 }, { 0, 129 }, { 0, 130 }, { 0, 131 }, { 0, 132 }, { 0, 133 }, { 0, 134 }, { 0, 135 },
    { 0, 136 }, { 0, 137 }, { 0, 138 }, { 0, 139 }, { 0, 140 }, { 0, 141 }, { 0, 142 }, { 0, 143 },
    { 0, 144 }, { 0, 145 }, { 0, 146 }, { 0, 147 }, { 0, 148 }, { 0, 149 }, { 0, 150 }, { 0, 151 },
    { 0, 152 }, { 0, 153 }, { 0, 154 }, { 0, 155 }, { 0, 156 }, { 0, 157 }, { 0, 158 }, { 0, 159 },
    { 0, 160 }, { 0, 161 }, { 0, 162 }, { 0, 163 }, { 0, 164 }, { 0, 165 }, { 0, 166 }, { 0, 167 },
    { 0, 168 }, { 1, 0 }, { 1, 1 }, { 1, 2 }, { 1, 3 }, { 1, 4 }, { 1, 5 }, { 1, 6 },
    { 1, 7 }, { 1, 8 }, { 1, 9 }, { 1, 10 }, { 1, 11 }, { 1, 12 }, { 1, 13 }, { 1, 14 },
    { 1, 15 }, { 1, 16 }, { 1, 17 }, { 1, 18 }, { 1, 19 }, { 1, 20 }, { 1, 21 }, { 1, 22 },
    { 1, 23 }, { 1, 24 }, { 1, 25 }, { 1, 26 }, { 1, 27 }, { 1, 28 }, { 1, 29 }, { 1, 30 },
    { 1, 31 }, { 1, 32 }, { 1, 33 }, { 1, 34 }, { 1, 35 }, { 1, 36 }, { 1, 37 }, { 1, 38 },
    { 1, 39 }, { 1, 40 }, { 1, 41 }, { 1, 42 }, { 1, 43 }, { 1, 44 }, { 1, 45 }, { 1, 46 },
    { 1, 47 }, { 1, 48 }, { 1, 49 }, { 1, 50 }, { 1, 51 }, { 1, 52 }, { 1, 53 }, { 1, 54 },
    { 1, 55 }, { 1, 56 }, { 1, 57 }, { 1, 58 }, { 1, 59 }, { 1, 60 }, { 1, 61 }, { 1, 62 },
    { 1, 63 }, { 1, 64 }, { 2, 0 }, { 2, 1 }, { 2, 2 }, { 2, 3 }, { 2, 4 }, { 2, 5 },
    { 2, 6 }, { 2, 7 }, { 2, 8 }, { 2, 9 }, { 2, 10 }, { 2, 11 }, { 2, 12 }, { 2, 13 },
    { 2, 14 }, { 2, 15 }, { 2, 16 }, { 2, 17 }, { 2, 18 }, { 2, 19 }, { 2, 20 }, { 2, 21 },
    { 2, 22 }, { 2, 23 }, { 2, 24 }, { 2, 25 }, { 2, 26 }, { 2, 27 }, { 2, 28 }, { 2, 29 },
    { 2, 30 }, { 2, 31 }, { 2, 32 }, { 2, 33 }, { 2, 34 }, { 2, 35 }, { 2, 36 }, { 2, 37 },
    { 2, 38 }, { 2, 39 }, { 2, 40 }, { 2, 41 }, { 2, 42 }, { 2, 43 }, { 2, 44 }, { 2, 45 },
    { 2, 46 }, { 2, 47 }, { 2, 48 }, { 2, 49 }, { 2, 50 }, { 2, 51 }, { 2, 52 }, { 2, 53 },
    { 2, 54 }, { 2, 55 }, { 2, 56 }, { 2, 57 }, { 2, 58 }, { 2, 59 }, { 2, 60 }, { 2, 61 },
    { 2, 62 }, { 2, 63 }, { 2, 64 }, { 2, 65 }, { 2, 66 }, { 2, 67 }, { 2, 68 }, { 2, 69 },
    { 2, 70 }, { 2, 71 }, { 2, 72 }, { 2, 73 }, { 2, 74 }, { 2, 75 }, { 2, 76 }, { 2, 77 },
    { 2, 78 }, { 2, 79 }, { 2, 80 }, { 2, 81 }, { 2, 82 }, { 2, 83 }, { 2, 84 }, { 2, 85 },
    { 2, 86 }, { 2, 87 }, { 2, 88 }, { 2, 89 }, { 2, 90 }, { 2, 91 }, { 2, 92 }, { 2, 93 },
    { 2, 94 }, { 2, 95 }, { 2, 96 }, { 2, 97 }, { 2, 98 }, { 2, 99 }, { 2, 100 }, { 2, 101 },
    { 2, 102 }, { 2, 103 }, { 2, 104 }, { 2, 105 }, { 2, 106 }, { 2, 107 }, { 2, 108 }, { 2, 109 },
    { 2, 110 }, { 2, 111 }, { 2, 112 }, { 2, 113 }, { 2, 114 }, { 2, 115 }, { 2, 116 }, { 2, 117 },
    { 2, 118 }, { 2, 119 }, { 2, 120 }, { 2, 121 }, { 2, 122 }, { 2, 123 }, { 2, 124 }, { 2, 125 },
    { 2, 126 }, { 2, 127 }, { 2, 128 }, { 2, 129 }, { 2, 130 }, { 2, 131 }, { 2, 132 }, { 2, 133 },
    { 2, 134 }, { 2, 135 }, { 3, 0 }, { 3, 1 }, { 3, 2 }, { 3, 3 }, { 3, 4 }, { 3, 5 },
    { 3, 6 }, { 3, 7 }, { 3, 8 }, { 3, 9 }, { 3, 10 }, { 3, 11 }, { 3, 12 }, { 3, 13 },
    { 3, 14 }, { 3, 15 }, { 3, 16 }, { 3, 17 }, { 3, 18 }, { 3, 19 }, { 3, 20 }, { 3, 21 },
    { 3, 22 }, { 3, 23 }, { 3, 24 }, { 3, 25 }, { 3, 26 }, { 3, 27 }, { 3, 28 }, { 3, 29 },
    { 3, 30 }, { 3, 31 }, { 3, 32 }, { 3, 33 }, { 3, 34 }, { 3, 35 }, { 3, 36 }, { 3, 37 },
    { 3, 38 }, { 3, 39 }, { 3, 40 }, { 3, 41 }, { 3, 42 }, { 3, 43 }, { 3, 44 }, { 3, 45 },
    { 3, 46 }, { 3, 47 }, { 3, 48 }, { 3, 49 }, { 3, 50 }, { 3, 51 }, { 3, 52 }, { 3, 53 },
    { 3, 54 }, { 3, 55 }, { 3, 56 }, { 3, 57 }, { 3, 58 }, { 3, 59 }, { 3, 60 }, { 3, 61 },
    { 3, 62 }, { 3, 63 }, { 3, 64 }, { 3, 65 }, { 3, 66 }, { 3, 67 }, { 3, 68 }, { 3, 69 },
    { 3, 70 }, { 3, 71 }, { 3, 72 }, { 3, 73 }, { 3, 74 }, { 3, 75 }, { 3, 76 }, { 3, 77 },
    { 3, 78 }, { 3, 79 }, { 3, 80 }, { 3, 81 }, { 3, 82 }, { 3, 83 }, { 3, 84 }, { 3, 85 },
    { 3, 86 }, { 3, 87 }, { 3, 88 }, { 3, 89 }, { 3, 90 }, { 3, 91 }, { 3, 92 }, { 3, 93 },
    { 3, 94 }, { 3, 95 }, { 3, 96 }, { 3, 97 }, { 3, 98 }, { 3, 99 }, { 3, 100 }, { 3, 101 },
    { 3, 102 }, { 3, 103 }, { 3, 104 }, { 3, 105 }, { 3, 106 }, { 3, 107 }, { 3, 108 }, { 3, 109 },
    { 3, 110 }, { 3, 111 }, { 3, 112 }, { 3, 113 }, { 3, 114 }, { 3, 115 }, { 3, 116 }, { 3, 117 },
    { 3, 118 }, { 3, 119 }, { 3, 120 }, { 4, 0 }, { 4, 1 }, { 4, 2 }, { 4, 3 }, { 4, 4 },
    { 4, 5 }, { 4, 6 }, { 4, 7 }, { 4, 8 }, { 4, 9 }, { 4, 10 }, { 4, 11 }, { 4, 12 },
    { 4, 13 }, { 4, 14 }, { 4, 15 }, { 4, 16 }, { 4, 17 }, { 4, 18 }, { 4, 19 }, { 4, 20 },
    { 4, 21 }, { 4, 22 }, { 4, 23 }, { 4, 24 }, { 4, 25 }, { 4, 26 }, { 4, 27 }, { 4, 28 },
    { 4, 29 }, { 4, 30 }, { 4, 31 }, { 4, 32 }, { 4, 33 }, { 4, 34 }, { 4, 35 }, { 4, 36 },
    { 4, 37 }, { 4, 38 }, { 4, 39 }, { 4, 40 }, { 4, 41 }, { 4, 42 }, { 4, 43 }, { 4, 44 },
    { 4, 45 }, { 4, 46 }, { 4, 47 }, { 4, 48 }, { 4, 49 }, { 4, 50 }, { 4, 51 }, { 4, 52 },
    { 4, 53 }, { 4, 54 }, { 4, 55 }, { 4, 56 }, { 4, 57 }, { 4, 58 }, { 4, 59 }, { 4, 60 },
    { 4, 61 }, { 4, 62 }, { 4, 63 }, { 4, 64 }, { 4, 65 }, { 4, 66 }, { 4, 67 }, { 4, 68 },
    { 4, 69 }, { 4, 70 }, { 4, 71 }, { 4, 72 }, { 4, 73 }, { 4, 74 }, { 4, 75 }, { 4, 76 },
    { 4, 77 }, { 4, 78 }, { 4, 79 }, { 4, 80 }, { 4, 81 }, { 4, 82 }, { 4, 83 }, { 4, 84 },
    { 4, 85 }, { 4, 86 }, { 4, 87 }, { 4, 88 }, { 4, 89 }, { 4, 90 }, { 4, 91 }, { 4, 92 },
    { 4, 93 }, { 4, 94 }, { 4, 95 }, { 4, 96 }, { 4, 97 }, { 4, 98 }, { 4, 99 }, { 4, 100 },
    { 4, 101 }, { 5, 0 }, { 5, 1 }, { 5, 2 }, { 5, 3 }, { 5, 4 }, { 5, 5 }, { 5, 6 },
    { 5, 7 }, { 5, 8 }, { 5, 9 }, { 5, 10 }, { 5, 11 }, { 5, 12 }, { 5, 13 }, { 5, 14 },
    { 5, 15 }, { 5, 16 }, { 5, 17 }, { 5, 18 }, { 5, 19 }, { 5, 20 }, { 5, 21 }, { 5, 22 },
    { 5, 23 }, { 5, 24 }, { 5, 25 }, { 5, 26 }, { 5, 27 }, { 5, 28 }, { 5, 29 }, { 5, 30 },
    { 5, 31 }, { 5, 32 }, { 5, 33 }, { 5, 34 }, { 5, 35 }, { 5, 36 }, { 5, 37 }, { 5, 38 },
    { 5, 39 }, { 5, 40 }, { 5, 41 }, { 5, 42 }, { 5, 43 }, { 5, 44 }, { 5, 45 }, { 5, 46 },
    { 5, 47 }, { 5, 48 }, { 5, 49 }, { 5, 50 }, { 5, 51 }, { 5, 52 }, { 5, 53 }, { 5, 54 },
    { 5, 55 }, { 5, 56 }, { 5, 57 }, { 5, 58 }, { 5, 59 }, { 5, 60 }, { 5, 61 }, { 5, 62 },
    { 5, 63 }, { 5, 64 }, { 5, 65 }, { 5, 66 }, { 5, 67 }, { 5, 68 }, { 5, 69 }, { 5, 70 },
    { 5, 71 }, { 5, 72 }, { 5, 73 }, { 5, 74 }, { 5, 75 }, { 5, 76 }, { 5, 77 }, { 5, 78 },
    { 5, 79 }, { 5, 80 }, { 5, 81 }, { 5, 82 }, { 5, 83 }, { 5, 84 }, { 5, 85 }, { 5, 86 },
    { 5, 87 }, { 5, 88 }, { 5, 89 }, { 5, 90 }, { 5, 91 }, { 5, 92 }, { 5, 93 }, { 5, 94 },
    { 5, 95 }, { 5, 96 }, { 5, 97 }, { 6, 0 }, { 6, 1 }, { 6, 2 }, { 6, 3 }, { 6, 4 },
    { 6, 5 }, { 6, 6 }, { 6, 7 }, { 6, 8 }, { 6, 9 }, { 6, 10 }, { 6, 11 }, { 6, 12 },
    { 6, 13 }, { 6, 14 }, { 6, 15 }, { 6, 16 }, { 6, 17 }, { 6, 18 }, { 6, 19 }, { 6, 20 },
    { 6, 21 }, { 6, 22 }, { 6, 23 }, { 6, 24 }, { 6, 25 }, { 6, 26 }, { 6, 27 }, { 6, 28 },
    { 6, 29 }, { 6, 30 }, { 6, 31 }, { 6, 32 }, { 6, 33 }, { 6, 34 }, { 6, 35 }, { 6, 36 },
    { 6, 37 }, { 6, 38 }, { 6, 39 }, { 6, 40 }, { 6, 41 }, { 6, 42 }, { 6, 43 }, { 6, 44 },
    { 6, 45 }, { 6, 46 }, { 6, 47 }, { 6, 48 }, { 6, 49 }, { 6, 50 }, { 6, 51 }, { 6, 52 },
    { 6, 53 }, { 6, 54 }, { 6, 55 }, { 6, 56 }, { 6, 57 }, { 6, 58 }, { 6, 59 }, { 6, 60 },
    { 6, 61 }, { 6, 62 }, { 6, 63 }, { 6, 64 }, { 6, 65 }, { 6, 66 }, { 6, 67 }, { 6, 68 },
    { 6, 69 }, { 6, 70 }, { 6, 71 }, { 6, 72 }, { 6, 73 }, { 6, 74 }, { 6, 75 }, { 6, 76 },
    { 6, 77 }, { 6, 78 }, { 6, 79 },
};

// Globals typed by worker dv02, from retail's bytes and their readers.

// Globals typed by worker dv06, from retail's bytes and their readers.
struct VEnt_0024A0E0 { s32 delta; void (*fn)(); };
struct VEnt_0024A220 { s32 delta; void (*fn)(); };
struct Vec2_24A210 { f32 x; f32 y; };
void func_00152E18();
void func_0015C2E8();
void func_0015C3C0();
void func_0015C930();
void func_0015CA38();
void func_0015CA60();
void func_0015CB88();
void func_0015CC80();
void func_0015CD18();
void func_0015CF70();
void func_0015D4E0();
void func_001FBDF8();

extern const f32 D_00249E4C = 3.4028235e+38f;
extern const char D_0024A2D0[8] = "Splash";
extern const char D_0024A2D8[16] = "Paris, France";
extern const char D_0024A2E8[16] = "The Hideout";
extern const char D_0024A2F8[24] = "A Stealthy Approach";
extern const char D_0024A310[24] = "Prowling the Grounds";
extern const char D_0024A328[24] = "High Class Heist";
extern const char D_0024A340[24] = "Into the Machine";
extern const char D_0024A358[24] = "A Cunning Disguise";
extern const char D_0024A370[24] = "The Fire Down Below";
extern const char D_0024A388[24] = "Treasure in the Depths";
extern const char D_0024A3A0[24] = "The Gunboat Graveyard";
extern const char D_0024A3B8[24] = "The Eye of the Storm";
extern const char D_0024A3D0[16] = "A Rocky Start";
extern const char D_0024A3E0[16] = "Muggshot's Turf";
extern const char D_0024A3F0[16] = "Boneyard Casino";
extern const char D_0024A400[24] = "Murray's Big Gamble";
extern const char D_0024A418[24] = "At the Dog Track";
extern const char D_0024A430[16] = "Two to Tango";
extern const char D_0024A440[24] = "Straight to the Top";
extern const char D_0024A458[24] = "Back Alley Heist";
extern const char D_0024A470[16] = "Last Call";
extern const char D_0024A480[24] = "The Dread Swamp Path";
extern const char D_0024A498[24] = "The Swamp's Dark Center";
extern const char D_0024A4B0[24] = "The Lair of the Beast";
extern const char D_0024A4C8[24] = "A Grave Undertaking";
extern const char D_0024A4E0[16] = "Piranha Lake";
extern const char D_0024A4F0[24] = "Descent into Danger";
extern const char D_0024A508[24] = "A Ghastly Voyage";
extern const char D_0024A520[24] = "Down Home Cooking";
extern const char D_0024A538[16] = "A Deadly Dance";
extern const char D_0024A548[24] = "A Perilous Ascent";
extern const char D_0024A560[24] = "Inside the Stronghold";
extern const char D_0024A578[24] = "Flaming Temple of Flame";
extern const char D_0024A590[16] = "The Unseen Foe";
extern const char D_0024A5A0[24] = "The King of the Hill";
extern const char D_0024A5B8[24] = "Rapid Fire Assault";
extern const char D_0024A5D0[24] = "Duel by the Dragon";
extern const char D_0024A5E8[24] = "A Desperate Race";
extern const char D_0024A600[16] = "Flame Fu!";
extern const char D_0024A610[24] = "A Hazardous Path";
extern const char D_0024A628[16] = "Burning Rubber";
extern const char D_0024A638[16] = "A Daring Rescue";
extern const char D_0024A648[24] = "Bentley Comes Through";
extern const char D_0024A660[24] = "A Temporary Truce";
extern const char D_0024A678[16] = "Sinking Peril";
extern const char D_0024A688[24] = "A Strange Reunion";

// Globals typed by worker dv07, from retail's bytes and their readers.

// Globals typed by worker dv08, from retail's bytes and their readers.
struct VtEnt_24F0D8 { s32 delta; void (*fn)(); };
void func_001FEF00();
void func_001FEFC0();
void func_001FF008();
void func_002005A0();
void func_002005E8();
void func_00200638();
void func_00200680();
extern const double D_0024E9C8 = 0.1;
extern const double D_0024E9D0 = 0.1;
extern const double D_0024E9D8 = 1000000.0;
extern const char D_0024EB78[3][8] = {"....", "....", "all"};
extern const char D_002504F8[48] = "Too small buffer size for %dx%d picture\n";

// Globals typed by worker dv03, from retail's bytes and their readers.
extern const u8 D_0026A0E0[];
extern const u8 D_0026A0E8[];
extern const u8 D_0026A0F0[];
extern const u8 D_0026A0F8[];
extern const u8 D_0026A100[];
extern const u8 D_0026A108[];
extern const u8 D_0026A110[];


// Globals typed by worker dv05, from retail's bytes and their readers.
extern const u8 D_002197B8[];
extern const u8 D_002198E8[];
extern const u8 D_002505B8[];
extern const char D_0024DCB0[];
extern const char D_0024DCC8[];
extern const char D_0024DCE8[];
extern const char D_0024DD38[];
extern const char D_0024DD60[];
extern const char D_0024DD80[];
extern const char D_0024DDA0[];
extern const char D_0024DDC8[];
extern const char D_0024DDF0[];
extern const char D_0024DE10[];
extern const char D_0024DE38[];
extern const char D_0024DE50[];
extern const char D_0024DE70[];
extern const char D_0024DE98[];
extern const char D_0024DEC0[];
extern const char D_0024DEF0[];
extern const char D_0024DF10[];
extern const char D_0024DF50[];
extern const char D_0024DF78[];
extern const char D_0024DFA0[];
extern const char D_0024DFB8[];
extern const char D_0024DFD8[];
extern const char D_0024DFF0[];
extern const char D_0024E018[];
extern const char D_0024E038[];
extern const char D_0024E060[];
extern const char D_0024E088[];
extern const char D_0024E0A8[];
extern const char D_0024E0C8[];
extern const char D_0024E0F8[];
extern const char D_0024E118[];
extern const u8 D_00278000[], D_00278050[], D_00278644[], D_002789DC[], D_00278A7C[], D_00278E88[];
volatile s32 D_00277138[32] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
s32 D_002771CC = -1;
extern const void* const D_00247448[149] = {
    &D_00217410,
    &D_00217418,
    &D_00217498,
    &D_00217568,
    &D_00220E20,
    &D_00217C30,
    &D_0021A838,
    &D_0021B688,
    &D_0021BB58,
    &D_0021BE98,
    &D_0021BCF8,
    &D_0021E728,
    &D_0021E8C8,
    &D_0021EA68,
    &D_0021F788,
    &D_0021FA88,
    &D_0021FE88,
    &D_00220028,
    &D_002201C8,
    &D_0021ED68,
    &D_0021F4B8,
    &D_0021D5B8,
    &D_0021F628,
    &D_0021D1D8,
    &D_0021F928,
    &D_00220438,
    &D_00220A90,
    &D_00220598,
    &D_0021EC08,
    &D_00220CC0,
    &D_00219AF0,
    &D_00218770,
    &D_00218970,
    &D_00218BD8,
    &D_0021A9D0,
    &D_0021DD08,
    &D_00220958,
    &D_00218D10,
    &D_00218E48,
    &D_00218AA8,
    &D_002190B0,
    &D_00218F80,
    &D_0021F058,
    &D_00219330,
    &D_0021CC78,
    &D_0021CDB8,
    &D_0021CEF8,
    &D_0021AB08,
    &D_0021AC38,
    &D_0021AD80,
    &D_0021AEC8,
    &D_0021B010,
    &D_0021B2D8,
    &D_002198F0,
    &D_0021C038,
    &D_0021C168,
    &D_0021C318,
    &D_0021E458,
    &D_0021A660,
    &D_0021B4D8,
    &D_0021DF10,
    &D_0021E048,
    &D_0021E180,
    &D_0021B878,
    &D_0021C598,
    &D_0021D3B8,
    &D_0021D718,
    &D_0021D848,
    &D_0021D978,
    &D_0021DAA8,
    &D_0021DBD8,
    &D_0021F188,
    &D_0021FC28,
    &D_0021FD58,
    &D_002206F8,
    &D_00220828,
    &D_0021B9A8,
    &D_00219F80,
    &D_00217A90,
    &D_00219260,
    &D_0021A050,
    &D_00217B60,
    &D_00219A20,
    &D_0021A320,
    &D_0021C4C8,
    &D_0021C6C8,
    &D_0021C868,
    &D_0021CAD8,
    &D_0021C798,
    &D_0021C938,
    &D_0021CA08,
    &D_0021CBA8,
    &D_0021D038,
    &D_0021D108,
    &D_0021B408,
    &D_0021D4E8,
    &D_0021DE40,
    &D_0021E588,
    &D_0021E658,
    &D_002188A0,
    &D_0021EF88,
    &D_0021A490,
    &D_00220F50,
    &D_00221020,
    &D_00220368,
    &D_00221210,
    &D_00221140,
    &D_002213D0,
    &D_002214A0,
    &D_00221520,
    &D_00217740,
    &D_0021A560,
    &D_0021B258,
    &D_0021F338,
    &D_0021F3B8,
    &D_002178C0,
    &D_00217940,
    &D_0021B158,
    &D_0021B1D8,
    &D_0021A120,
    &D_0021A1A0,
    &D_0021A220,
    &D_0021A2A0,
    &D_0021C298,
    &D_0021D338,
    &D_002179C0,
    &D_002177C0,
    &D_0021A5E0,
    &D_0021B7F8,
    &D_0021F2B8,
    &D_00217840,
    &D_00219738,
    &D_002197E8,
    &D_002194E0,
    &D_00219460,
    &D_002191E0,
    &D_00219868,
    &D_0021BAD8,
    &D_0021C448,
    &D_0021A7B8,
    &D_0021E2B8,
    &D_0021F438,
    &D_00218650,
    &D_0021B608,
    &D_0021EF08,
    &D_00220C40,
    &D_002197B8,
    &D_002198E8,
    &D_002505B8
};
extern const u32 D_002476A0[256] = {
    0x00000000, 0x77073096, 0xEE0E612C, 0x990951BA, 0x076DC419, 0x706AF48F, 0xE963A535, 0x9E6495A3,
    0x0EDB8832, 0x79DCB8A4, 0xE0D5E91E, 0x97D2D988, 0x09B64C2B, 0x7EB17CBD, 0xE7B82D07, 0x90BF1D91,
    0x1DB71064, 0x6AB020F2, 0xF3B97148, 0x84BE41DE, 0x1ADAD47D, 0x6DDDE4EB, 0xF4D4B551, 0x83D385C7,
    0x136C9856, 0x646BA8C0, 0xFD62F97A, 0x8A65C9EC, 0x14015C4F, 0x63066CD9, 0xFA0F3D63, 0x8D080DF5,
    0x3B6E20C8, 0x4C69105E, 0xD56041E4, 0xA2677172, 0x3C03E4D1, 0x4B04D447, 0xD20D85FD, 0xA50AB56B,
    0x35B5A8FA, 0x42B2986C, 0xDBBBC9D6, 0xACBCF940, 0x32D86CE3, 0x45DF5C75, 0xDCD60DCF, 0xABD13D59,
    0x26D930AC, 0x51DE003A, 0xC8D75180, 0xBFD06116, 0x21B4F4B5, 0x56B3C423, 0xCFBA9599, 0xB8BDA50F,
    0x2802B89E, 0x5F058808, 0xC60CD9B2, 0xB10BE924, 0x2F6F7C87, 0x58684C11, 0xC1611DAB, 0xB6662D3D,
    0x76DC4190, 0x01DB7106, 0x98D220BC, 0xEFD5102A, 0x71B18589, 0x06B6B51F, 0x9FBFE4A5, 0xE8B8D433,
    0x7807C9A2, 0x0F00F934, 0x9609A88E, 0xE10E9818, 0x7F6A0DBB, 0x086D3D2D, 0x91646C97, 0xE6635C01,
    0x6B6B51F4, 0x1C6C6162, 0x856530D8, 0xF262004E, 0x6C0695ED, 0x1B01A57B, 0x8208F4C1, 0xF50FC457,
    0x65B0D9C6, 0x12B7E950, 0x8BBEB8EA, 0xFCB9887C, 0x62DD1DDF, 0x15DA2D49, 0x8CD37CF3, 0xFBD44C65,
    0x4DB26158, 0x3AB551CE, 0xA3BC0074, 0xD4BB30E2, 0x4ADFA541, 0x3DD895D7, 0xA4D1C46D, 0xD3D6F4FB,
    0x4369E96A, 0x346ED9FC, 0xAD678846, 0xDA60B8D0, 0x44042D73, 0x33031DE5, 0xAA0A4C5F, 0xDD0D7CC9,
    0x5005713C, 0x270241AA, 0xBE0B1010, 0xC90C2086, 0x5768B525, 0x206F85B3, 0xB966D409, 0xCE61E49F,
    0x5EDEF90E, 0x29D9C998, 0xB0D09822, 0xC7D7A8B4, 0x59B33D17, 0x2EB40D81, 0xB7BD5C3B, 0xC0BA6CAD,
    0xEDB88320, 0x9ABFB3B6, 0x03B6E20C, 0x74B1D29A, 0xEAD54739, 0x9DD277AF, 0x04DB2615, 0x73DC1683,
    0xE3630B12, 0x94643B84, 0x0D6D6A3E, 0x7A6A5AA8, 0xE40ECF0B, 0x9309FF9D, 0x0A00AE27, 0x7D079EB1,
    0xF00F9344, 0x8708A3D2, 0x1E01F268, 0x6906C2FE, 0xF762575D, 0x806567CB, 0x196C3671, 0x6E6B06E7,
    0xFED41B76, 0x89D32BE0, 0x10DA7A5A, 0x67DD4ACC, 0xF9B9DF6F, 0x8EBEEFF9, 0x17B7BE43, 0x60B08ED5,
    0xD6D6A3E8, 0xA1D1937E, 0x38D8C2C4, 0x4FDFF252, 0xD1BB67F1, 0xA6BC5767, 0x3FB506DD, 0x48B2364B,
    0xD80D2BDA, 0xAF0A1B4C, 0x36034AF6, 0x41047A60, 0xDF60EFC3, 0xA867DF55, 0x316E8EEF, 0x4669BE79,
    0xCB61B38C, 0xBC66831A, 0x256FD2A0, 0x5268E236, 0xCC0C7795, 0xBB0B4703, 0x220216B9, 0x5505262F,
    0xC5BA3BBE, 0xB2BD0B28, 0x2BB45A92, 0x5CB36A04, 0xC2D7FFA7, 0xB5D0CF31, 0x2CD99E8B, 0x5BDEAE1D,
    0x9B64C2B0, 0xEC63F226, 0x756AA39C, 0x026D930A, 0x9C0906A9, 0xEB0E363F, 0x72076785, 0x05005713,
    0x95BF4A82, 0xE2B87A14, 0x7BB12BAE, 0x0CB61B38, 0x92D28E9B, 0xE5D5BE0D, 0x7CDCEFB7, 0x0BDBDF21,
    0x86D3D2D4, 0xF1D4E242, 0x68DDB3F8, 0x1FDA836E, 0x81BE16CD, 0xF6B9265B, 0x6FB077E1, 0x18B74777,
    0x88085AE6, 0xFF0F6A70, 0x66063BCA, 0x11010B5C, 0x8F659EFF, 0xF862AE69, 0x616BFFD3, 0x166CCF45,
    0xA00AE278, 0xD70DD2EE, 0x4E048354, 0x3903B3C2, 0xA7672661, 0xD06016F7, 0x4969474D, 0x3E6E77DB,
    0xAED16A4A, 0xD9D65ADC, 0x40DF0B66, 0x37D83BF0, 0xA9BCAE53, 0xDEBB9EC5, 0x47B2CF7F, 0x30B5FFE9,
    0xBDBDF21C, 0xCABAC28A, 0x53B39330, 0x24B4A3A6, 0xBAD03605, 0xCDD70693, 0x54DE5729, 0x23D967BF,
    0xB3667A2E, 0xC4614AB8, 0x5D681B02, 0x2A6F2B94, 0xB40BBE37, 0xC30C8EA1, 0x5A05DF1B, 0x2D02EF8D
};
extern const u32 D_00247AB0[8] = { 0xFDC02D54, 0x0AB32899, 0x6BD9B0B8, 0x3C8FB5B8, 0x02EF0F96, 0xFDCCA9C0, 0x6BD9B0AD, 0x0AB165D8 };
extern const u32 D_00247AD0[8] = { 0x2F5A2B8C, 0x7C1B2134, 0xF6CA6520, 0x75002C27, 0xB708AA18, 0x2F5705BF, 0xF6CA6529, 0x7C35CE16 };
// Moved from 0016C000.cpp when the player's file (file_16F608.cpp) took its functions.
struct Slot_2482D8 { u32 w[8]; };
extern const Slot_2482D8 D_002482D8[7] = {
    {0x239C1F4B, 0x4F1B6BCE, 0x332880C9, 0xDC1FC810, 0xB3EF7189, 0x239FB500, 0x332882F6, 0x4F1B486E},
    {0x674A1AEF, 0xEAAAB4AD, 0xCE2EF724, 0xB0B61237, 0x30E7A079, 0x67448204, 0xCE2EF564, 0xEAAA8C7D},
    {0x9FFD39A4, 0x92C0B086, 0x1904453E, 0x13763226, 0x52A098D3, 0x9FFD0941, 0x1904477F, 0x92C08E66},
    {0x631F4A84, 0xB9572D78, 0xA364788C, 0xBAF57CFC, 0xB7D7C188, 0x63176250, 0xA3647ACE, 0xB9571298},
    {0x816C657F, 0xB563A94D, 0x90993FD9, 0x2B5164CE, 0xA46DB733, 0x81696BC7, 0x90993D9A, 0xB563EFCD},
    {0xD4312CB4, 0xC376AE2A, 0x8D50D2C3, 0xC7A8D28C, 0x39A7CE66, 0xD422EB19, 0x8D50D087, 0xC3769B7A},
    {0x3909A2A2, 0xDA5D87C2, 0xC3446569, 0x59D126B9, 0x6943323B, 0x390995E6, 0xC344672C, 0xDA5DAE02}
};

extern const char D_002483B8[24] = "@KFWHJGL";

extern const Mat02 D_002483D0 = { { { 1.0f, 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f, 0.0f } } };
extern const f32 D_00248400[28] = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
extern const Vec02 D_00248D00 = { 1.0f, 0.0f, 0.0f, 0.0f };
extern const Vec02 D_00248D10 = { 0.0f, 1.0f, 0.0f, 0.0f };
extern const Vec02 D_00248D20 = { 0.0f, 0.0f, 1.0f, 0.0f };
extern const f32 D_00248D40[4] = { 1.0f, 1.0f, 1.0f, 0.0f };
extern const f32 D_00248D50[4] = { 3.40282347e+38f, 3.40282347e+38f, 3.40282347e+38f, 0.0f };

// Globals typed by worker dv01, from retail's bytes and their readers.
struct Rec_263558 { s32 f0; s32 f4; s32 f8; };

f32 D_00261CD4 = 500.0f;
f32 D_00261CD8 = 800.0f;
ThresholdRange D_00261D40[4] = {
    { 0.8f, 2, 5 }, { 0.4f, 6, 10 }, { 0.2f, 15, 25 }, { 0.0f, 50, 100 }
};
f32 D_00262178[2] = { 0.5f, 2.0f };
f32 D_002621F8[6] = { 7.0f, 1.0f, 0.25f, 0.0f, 0.0f, 0.0f };
f32 D_00262210[4] = { 0.0f, 0.25f, 0.000250000012f, 0.0f };
f32 D_00262220[4] = { 0.0f, 0.25f, 0.0250000004f, 0.0f };
char D_00262250[8] = "02134";
s32 D_002622CC = 1;
GameProgress* D_002623C0 = &D_0027C220;
G27C230* D_002623C4 = D_0027C230;
G27C230* D_002623C8 = D_0027C230;
s32 D_002623CC = -1;

// Globals typed by worker dz06, from retail's bytes and their readers.
// word
// word flag
// word
// word
// word flag
// word flag
// word

// Globals typed by worker dz07, from retail's bytes and their readers.

// size: s32 read as one word (func_00150000.cpp and 001AC000.cpp test bit 8)
// size: s32 compared with 1/2 in 00148000 and 00194000
// size: func_0012A610/func_0012A6E0 copy it as a 16-byte vector
// size: s32 state compared/assigned in 001EC000
// size: u32 cleared by func_001F7D88
u32 D_00277134 = 0;
// size: s32 flag set/cleared in 001F8000
s32 D_002771B8 = 0;

// Globals typed by worker dz05, from retail's bytes and their readers.
// size: lw at offset 0 only, a 4-byte scalar of its own label
extern s32 D_00270454;
// size: lw at offset 0 (a pointer, read with lqc2 0x140 off it), 4-byte label
extern void* D_002704F4;
// size: lw at offset 0 compared with 1, 4-byte label
extern s32 D_00270518;
// size: lw at offset 0 compared with a count, 4-byte label
extern s32 D_002726AC;
// size: lw at offset 0 compared with a count, 4-byte label
extern s32 D_0027292C;

// Globals typed by worker dz02, from retail's bytes and their readers.
// size: s32 counter (lw/sw), 4 bytes before an 8-aligned next label
s32 D_00261D38 = 0;
// size: func_00151A68 clears 0x24 bytes of it
G261EF0 D_00261EF0 = {};
// size: semaphore id from func_002027A0 (lw/sw), 4-byte label
s32 D_00261F14 = 0;
s32 D_00261F18 = 0;
s32 D_00261F1C = 0;
s32 D_00261F20 = 0;
// size: s32 (lw/sw), 4-byte label
s32 D_00261F70 = 0;
// size: s32 (lw/sw), 4-byte label
s32 D_00262260 = 0;
// size: pointer to array allocated by new Ent[D_00262260] (lw/sw), 4-byte label
u8* D_00262264 = 0;
// size: loop bound 5, stride 4 in func_0015C200
s32 D_00262268[5] = {0};
// size: s32 (lw/sw), 4-byte label
s32 D_0026227C = 0;
// size: s32 (lw/sw), 4-byte label
s32 D_002622D0 = 0;
// size: s32 (lw/sw), 4-byte label
s32 D_002622D4 = 0;
// size: pointer (lw/sw), 4 bytes before an 8-aligned next label
RenderFrame* D_002622D8 = 0;
// size: 12-byte record copied into Slot r20 by func_0015EC68, 4 bytes pad before 16-aligned next label
List01 D_002622E0 = {};
// size: 12-byte record copied into Slot r2C by func_0015EC68, 4 bytes pad before 16-aligned next label
List01 D_002622F0 = {};
// size: 12-byte record copied into Slot r38 by func_0015EC68
List01 D_00262300 = {};
// size: s32 (sw), 4-byte label
s32 D_00262310 = 0;
// size: s32 (lw/sw), 4-byte label
s32 D_00262318 = 0;
// size: func_0015E810 loops 2 records of stride 0x48 (end = base + 0x90)
RenderFrame D_00262320[2] = {};
// size: pointer (lw/sw), 4-byte label
void* D_002623B4 = 0;

// Globals typed by worker dz04, from retail's bytes and their readers.
// size: readers use it as an f32 (lwc1/swc1), label is 4 bytes
// size: readers use it as an f32 (lwc1/swc1), label is 4 bytes
// size: readers use it as an f32 (lwc1/swc1), label is 4 bytes
// size: readers use it as an f32 (lwc1/swc1), label is 4 bytes
// size: func_0019DF48 fills 18 rows of 0x80 bytes (fn at +0, -1 at +8; loop i=17..0, stride 0x80) = 0x900
// size: one s32 (lw, compared with 2), label 8 bytes with 4 of padding before the 8-aligned D_0026EC60
extern s32 D_0026EC58;
// size: one s32 (lw, compared with 0), label 8 bytes with 4 of padding before the 8-aligned D_0026EC68
extern s32 D_0026EC60;
// size: one pointer (lw, passed to func_00150790), label 8 bytes with 4 of padding before the 8-aligned D_0026F808
extern u8* D_0026F800;
// size: one s32 (lw, bnez), label is 4 bytes
extern s32 D_0026FA64;

// Globals typed by worker dz01, from retail's bytes and their readers.

// The span func_00130F48 fills: head, then len/halfw/lo/mid/hi/p/q, padded to 16 by the quad's alignment.

// size: sizeof(Span_261280) == 0x30; func_00130F48 fills it (n = 0x18) and func_00131000 reads it
// size: same Span type, 0x30, filled by func_00130F48 at 0x131418 and read by func_00131000
// size: same Span type, 0x30, filled by func_00130F48 at 0x131444 and read by func_00131000
// size: one f32, read and written only with lwc1/swc1 (0x1312B8..0x131B48)

// Globals typed by worker dz03, from retail's bytes and their readers.
// A list head: first and last item, and the offset of the link inside an item (func_00152460 adds it).
// Three words set by func_00168D68.
// Record func_0016C360 clears (0x1C bytes) and fills.
struct Pair_262C70 { f32 lo; f32 hi; };
// The input stream func_0016E1A0 clears (0xC4 bytes).
struct Obj_262C70 {
    u8 pad00[4];
    s32 f04;
    s32 f08;
    s32 f0C;
    s32 f10;
    s32 f14;
    s32 f18;
    f32 f1C;
    s32 f20;
    u8 pad24[0x2C];
    s32 f50;
    Pair_262C70 a54[4];
    u8 pad74[0x10];
    s32 f84;
    Pair_262C70 a88[4];
    s16 fA8;
    u8 padAA[0x12];
    void* fBC;
    s32 fC0;
};
struct Obj_2629A8 { u8 pad0[4]; u8 b4; u8 pad5[3]; f32 f8; f32 fC; f32 f10; f32 f14; s32 w18; };

// size: pointer, word accesses only
// size: s32, word load/store only
// size: pointer, word store of D_002622CC
// size: s32, word accesses only
// size: func_00184DE8 fills it while index < 0x100 (sltiu 0x100, step 4)
// size: s32 count, tested < 0x10 against the D_00264670 table in func_00184DE8
// size: func_00184DE8 adds entries while count < 0x10, stride 0x10 (sll 4)
// size: s32 flag, word load/store only
// size: func_00193940 loops 1 <= i < 3 over elements of stride 0x1A5C (the full table is 3 * 0x1A5C = 0x4F14)
// size: func_0018B5C0 sets words +0, +4, +0x10 (0x14 bytes)
extern BackgroundJob D_00269990;
// size: s32, word load/store only
// size: s32 counter, word load/store only
extern const LevelEntry D_00248748[33] = {
    { 0x00000100, 77.0f, { 0xB4D572D8, 0xF825BBFB, 0xD81D7156, 0x397F5178, 0x728793AF, 0xB4DDCF33, 0xD81D73EC, 0xF8032CCB }, D_0024DCB0 },
    { 0x00000102, 60.0f, { 0x2D97B868, 0x3B2491E4, 0x149B5E84, 0xED6063AB, 0xEC614227, 0x2D9472EA, 0x149B5C3C, 0x3B063804 }, D_0024DCC8 },
    { 0x00000103, 139.0f, { 0x7EA0F65C, 0xD2337F06, 0xBE2AFC49, 0x12C36311, 0x7C279683, 0x7EA42098, 0xBE2AFEF0, 0xD22162E6 }, D_0024DCE8 },
    { 0x00000104, 90.0f, { 0x43450000, 0x1BA9F623, 0xD50CE115, 0x2C1200AF, 0xCEA641C8, 0x4356A7CF, 0xD50CE3A2, 0x1B896FC3 }, D_0024DD38 },
    { 0x00000105, 92.0f, { 0x99CE9B7C, 0x71906A24, 0xF0C28B06, 0xEB485F8B, 0x53B61FF1, 0x99DD5CC8, 0xF0C289B0, 0x71B1D014 }, D_0024DD60 },
    { 0x00000106, 0.0f, { 0x2699F11C, 0x49A028DA, 0x4F211F07, 0x48124182, 0x178D0C5F, 0x269A54DB, 0x4F211DBC, 0x4984311A }, D_0024DD80 },
    { 0x00000107, 70.0f, { 0x58F37394, 0x1350631B, 0x01CBDC91, 0x44F71ECF, 0xDF5726B9, 0x58F33959, 0x01CBDE2D, 0x1372669B }, D_0024DDA0 },
    { 0x00000200, 90.0f, { 0xD0F1FFA7, 0xC60FB906, 0xF6CBF1E8, 0xDBDFC7A2, 0x60C39D81, 0xD0F25069, 0xF6CBF340, 0xC62CF876 }, D_0024DDC8 },
    { 0x00000202, 135.0f, { 0x8D75C2BA, 0x1C60DBC3, 0x87B409B3, 0xE1C1EC55, 0x1628B119, 0x8D73AF2A, 0x87B40B1A, 0x1C4054D3 }, D_0024DDF0 },
    { 0x00000203, 80.0f, { 0xEFF2D448, 0xCD3CF9B6, 0x643C8676, 0xEE4BB37E, 0x5221084A, 0xEFFBDEE7, 0x643C84DA, 0xCD29D486 }, D_0024DD80 },
    { 0x00000204, 0.0f, { 0x085CFED8, 0x500DEAB1, 0x2D8244CE, 0x20D7E0BD, 0x7B9BF59A, 0x084F301B, 0x2D824663, 0x50119521 }, D_0024DE10 },
    { 0x00000205, 118.0f, { 0x34B8FDC0, 0xBA921EE9, 0xBC440B92, 0xF084CB5F, 0x9B5D7162, 0x34B8BB9E, 0xBC440938, 0xBAB16B39 }, D_0024DE38 },
    { 0x00000206, 77.0f, { 0x1C7E6EEE, 0x3905F736, 0x84C0AC66, 0xF3ECEA0D, 0xF49EA1A6, 0x1C7E59A4, 0x84C0AECD, 0x39225AD6 }, D_0024DCC8 },
    { 0x00000207, 83.0f, { 0x22F88C24, 0x981BED54, 0xBE8B1621, 0xC6B35547, 0x244B7E13, 0x22FEE53D, 0xBE8B148F, 0x98385A04 }, D_0024DE50 },
    { 0x00000300, 95.0f, { 0x255C8D9D, 0xC67DD187, 0xB30FF9E1, 0xC0220E2F, 0x42968B68, 0x25585E92, 0xB30FFB5C, 0xC6607257 }, D_0024DE70 },
    { 0x00000302, 122.0f, { 0x95E88262, 0x256551E6, 0x4ADF2CC3, 0x3DB989E3, 0xB6A6B35A, 0x95EB4CBA, 0x4ADF2E00, 0x2543D296 }, D_0024DE98 },
    { 0x00000303, 138.0f, { 0x11AF8222, 0x4154CCCF, 0x0079AF5D, 0xE4F21BF0, 0x4D1A9134, 0x11BB038E, 0x0079ADE2, 0x414910EF }, D_0024DEC0 },
    { 0x00000304, 0.0f, { 0x4E5C5D94, 0x9A873808, 0x96FFEFBF, 0x8BD43856, 0x4D5F0EF3, 0x4E53B0C4, 0x96FFED7E, 0x9A95DB18 }, D_0024DEF0 },
    { 0x00000305, 128.0f, { 0xF98CB02D, 0xA283FC15, 0x25BB5DC0, 0xE157D974, 0x79983E9E, 0xF989BEEC, 0x25BB5F02, 0xA29D9135 }, D_0024DF10 },
    { 0x00000306, 0.0f, { 0xCD08BB18, 0xE7BF9B3F, 0xC95EE322, 0xE910E326, 0x9644F239, 0xCD09B122, 0xC95EE1E2, 0xE799CE4F }, D_0024DF50 },
    { 0x00000307, 0.0f, { 0x675AB398, 0xCDC3F75B, 0x04221B83, 0x8816DEE1, 0xC808ED2E, 0x675C5565, 0x0422193D, 0xCDD7A0DB }, D_0024DF78 },
    { 0x00000400, 129.0f, { 0x690D68D5, 0x91BE10E9, 0x53BEE0CB, 0x2DD4C53B, 0x34B03761, 0x691EC614, 0x53BEE264, 0x91A1B799 }, D_0024DFA0 },
    { 0x00000402, 135.0f, { 0xCDE8339C, 0xA52C25B6, 0x7A1C3B47, 0x60EAC381, 0x5CCA62D2, 0xCDE6A0FA, 0x7A1C39F5, 0xA50AE286 }, D_0024DFB8 },
    { 0x00000403, 145.0f, { 0x2E641117, 0x48B11069, 0x55A7DCBF, 0xBEE1993E, 0x68804E34, 0x2E651ED2, 0x55A7DE0F, 0x4894DAA9 }, D_0024DFD8 },
    { 0x00000404, 165.0f, { 0x67AF3B57, 0xF492F4FB, 0x4582A324, 0x58A7E5D7, 0x19037D39, 0x67BCF0BB, 0x4582A197, 0xF48440DB }, D_0024DFF0 },
    { 0x00000405, 0.0f, { 0x39FDBB59, 0x61874FF5, 0x431AA733, 0x1BF9BD2A, 0xD8FC45CE, 0x39E904E7, 0x431AA586, 0x619A0B55 }, D_0024E018 },
    { 0x00000406, 162.0f, { 0x130F1A4B, 0xF165A43C, 0x1085A760, 0x7EF09D87, 0xEEDC6182, 0x130BC343, 0x1085A5D1, 0xF17A745C }, D_0024E038 },
    { 0x00000407, 0.0f, { 0xAEE1B3B0, 0x23F21A5C, 0x2C5069FC, 0x69DA4B36, 0x2EFC59A8, 0xAEE1800D, 0x2C506B48, 0x23E4C85C }, D_0024E060 },
    { 0x00000502, 0.0f, { 0xE03513A1, 0xDF69E228, 0xBCC1BC75, 0x66B59F20, 0x5603C88D, 0xE0251B60, 0xBCC1BED2, 0xDF776558 }, D_0024E088 },
    { 0x00000503, 0.0f, { 0x10003460, 0x2357C8AB, 0x82DF6820, 0x9EA4EEF0, 0x67FFDE84, 0x101449AA, 0x82DF6A86, 0x2348C7EB }, D_0024E0A8 },
    { 0x00000504, 0.0f, { 0xC0351F76, 0xAEA9D7A0, 0xA96A1A69, 0x5A238437, 0x525CDAB3, 0xC03D3461, 0xA96A18CA, 0xAE889780 }, D_0024E0C8 },
    { 0x00000505, 0.0f, { 0x166B5E9F, 0xD83C11E9, 0x64ED4809, 0x9F137E03, 0x544B9C1C, 0x167F901D, 0x64ED4AAC, 0xD82147F9 }, D_0024E0F8 },
    { 0x00000506, 0.0f, { 0x9CD62C23, 0x9AB39D3E, 0xEA6D2E63, 0xFEC5BF26, 0xC170A675, 0x9CD0481B, 0xEA6D2CC7, 0x9A96D39E }, D_0024E118 },
};

// Globals typed by worker dz08, from retail's bytes and their readers.
struct Obj_26EC70 {
    const void* vt;
    u8 pad04[0x25C];
};

// size: func_0014ABD0 builds 4 embedded objects with this vtable (D_00218330) at stride 0x260
extern Obj_26EC70 D_0026EC70;

// Globals typed by worker dz201, from retail's bytes and their readers.
struct Obj_2639B8 { s32 f0; u8 pad04[4]; };

// 16 bytes, a pointer word read whole, rest padding
// 16 bytes, address passed (byte array in readers)
// 208 bytes, address only
// 16 bytes, byte array in readers
// 208 bytes, address only
// 8 bytes, one word read whole
// 24 bytes, byte array in readers
// 24 bytes, byte array in readers

// Globals typed by worker dz202, from retail's bytes and their readers.

// only address/offsets used by readers; size to next label
extern u8 D_0026C6C8[640];
// only address/offsets used by readers; size to next label
extern u8 D_0026C948[640];
// only address/offsets used by readers; size to next label
extern u8 D_0026CBC8[640];
// only address/offsets used by readers; size to next label
extern u8 D_0026CE48[640];
// only address/offsets used by readers; size to next label
extern u8 D_0026D0C8[640];
// only address/offsets used by readers; size to next label
extern u8 D_0026D348[640];
// only address/offsets used by readers; size to next label
extern u8 D_0026D5C8[640];
// only address/offsets used by readers; size to next label
extern u8 D_0026D848[612];
// only address/offsets used by readers; size to next label
// only address/offsets used by readers; size to next label
extern u8 D_0026DAC8[640];
// only address/offsets used by readers; size to next label
extern u8 D_0026DD48[640];
// only address/offsets used by readers; size to next label
extern u8 D_0026DFC8[608];
// only address/offsets used by readers; size to next label
extern u8 D_0026E248[664];
// only address/offsets used by readers; size to next label
extern u8 D_0026E4E0[612];

// Globals typed by worker dz203, from retail's bytes and their readers.
struct Obj_26EED0 { u8* head; u8 pad[612]; };
struct Obj_26F388 { s32 head; u8 pad[532]; };
struct Obj_26FA68 { void* head; u8 pad[36]; };
struct Obj_2701B8 { s32 head; u8 pad[8]; };

// object passed by address; size to next label
extern u8 D_0026E760[664];

// object read at offsets by several readers; size to next label
extern u8 D_0026E9F8[608];

// pointer stored at +0; size to next label
extern Obj_26EED0 D_0026EED0;

// object with vtable, size to next label
extern u8 D_0026F138[592];

// word read at +0; size to next label
extern Obj_26F388 D_0026F388;

// object; size to next label
extern u8 D_0026F5A0[608];

// object; size to next label
extern u8 D_0026F808[604];

// pointer read at +0; size to next label
extern Obj_26FA68 D_0026FA68;

// object with vtable; size to next label
extern u8 D_0026FA90[608];

// size: s32, the current placed object (g_currentPlacedObject), 4 bytes before the 16-aligned next label
extern s32 D_0026FCF0;

// object; size to next label
extern u8 D_0026FD00[616];

// object; size to next label
extern u8 D_0026FF68[592];

// word read at +0; size to next label
extern Obj_2701B8 D_002701B8;

// object; size to next label
extern u8 D_002701F8[592];

// Globals typed by worker dz204, from retail's bytes and their readers.
extern s32 D_00270448[3]; // 12 bytes to next label; word read whole at 0, rest padding
extern s32 D_00270458[39]; // 156 bytes; state word read whole at 0, word array to next label
extern u8 D_00270650[624]; // 624 bytes; accessed by offsets (0x284,0x288), byte buffer
extern u8 D_002708C0[32]; // 32 bytes; only address used
extern u8 D_002708E0[592]; // 592 bytes; object passed by address
extern s32 D_00270B30[9]; // 36 bytes; word read whole at 0
extern u8 D_00271558[592]; // 592 bytes; object passed by address
extern s32 D_002717A8[9]; // 36 bytes; word read whole at 0
extern u8 D_002721D0[572]; // 572 bytes; engine object used by address
extern s32 D_00272420[4]; // 16 bytes; word read whole at 0
extern u8 D_00272430[636]; // 636 bytes; block cast to structs by address
extern u8 D_002726B0[636]; // 636 bytes; block cast to structs by address
extern u8 D_00272930[572]; // 572 bytes; object with vt at 0, used by address

// Globals typed by worker dz205, from retail's bytes and their readers.
// readers pass only its address; byte buffer, size to next label
extern u8 D_00272B98[624];
// readers pass only its address; byte buffer, size to next label
extern u8 D_00272E08[3048];
// readers pass only its address; byte buffer, size to next label
extern u8 D_002739F0[608];
// readers pass only its address; byte buffer, size to next label
extern u8 D_00273C50[608];
// readers pass only its address; byte buffer, size to next label
extern u8 D_00273EB0[616];
// readers pass only its address; byte buffer, size to next label
extern u8 D_00274118[648];
// word read whole / address only, 4 bytes to next label
// readers pass only its address; byte buffer, size to next label
// word read whole / address only, 4 bytes to next label
// word read whole / address only, 4 bytes to next label


// Defined in the old 001EC000.cpp; outside file_1E88D0.cpp's data.
void* D_002505C0[6];


// Outside src/main/file_146100.cpp's and src/main/file_149398.cpp's data; read by func_00148718.
extern void* D_0026EC68;
