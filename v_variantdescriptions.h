/* VARIANT 0
   Everything has to be done manually by the user
   Encoder works normal
   Step: SigIn advances the cylinder one chamber clockwise
   Trigger: Button/SigIn pulls the trigger
   Spin: Button/SigIn spins the cylinder
   Insert: Button/SigIn inserts/removes a bullet from current chamber
   Add: Button/SigIn adds a chamber to the cylinder 2->3->...->12->2->3->...
   HIT: SigOut if the trigger hits a full chamber
   MISS: SigOut if the trigger hits a empty chamber
*/
const char desc_variant_0[] =
  "\"MANUAL\"\n\n>Do it Yourself!";

/* VARIANT 1
  Vanilla mode, barrel steps forward after trigger, if last bullet fired, 1 refill and spin
  Encoder works normal
  Step: SigIn advances the cylinder one chamber clockwise
  Trigger: Button/SigIn pulls the trigger and advances the cylinder one chamber clockwise
    BUT: if the last bullet is fired, a bullet is inserted and the cylinder spun
  Spin: Button/SigIn spins the cylinder
  Insert: Button/SigIn inserts/removes a bullet from current chamber
  Add: Button/SigIn adds a chamber to the cylinder 2->3->...->12->2->3->...
  HIT: SigOut if the trigger hits a full chamber
  MISS: SigOut if the trigger hits a empty chamber
*/
const char desc_variant_1[] =
  "\"VANILLA\"\n\n>trigger advances\n cylinder\n>refill and spin on\n last bullet";

/* VARIANT 2
  like vanilla, but bullet is not removed
  Encoder works normal
  Step: SigIn advances the cylinder one chamber clockwise
  Trigger: Button/SigIn pulls the trigger and spins it
    BUT: if the last bullet is fired, a bullet is inserted and the cylinder spun
  Spin: Button/SigIn spins the cylinder
  Insert: Button/SigIn inserts/removes a bullet from current chamber
  Add: Button/SigIn adds a chamber to the cylinder 2->3->...->12->2->3->...
  HIT: SigOut if the trigger hits a full chamber
  MISS: SigOut if the trigger hits a empty chamber
*/
const char desc_variant_2[] =
  "\"VANILLA NO REMOVAL\"\n\n>trigger advances\n cylinder\n>bullets are not\n removed";

/* VARIANT 3
  like vanilla, but after each trigger barrel spins
  Encoder works normal
  Step: SigIn advances the cylinder one chamber clockwise
  Trigger: Button/SigIn pulls the trigger and spins it
    BUT: if the last bullet is fired, a bullet is inserted and the cylinder spun
  Spin: Button/SigIn spins the cylinder
  Insert: Button/SigIn inserts/removes a bullet from current chamber
  Add: Button/SigIn adds a chamber to the cylinder 2->3->...->12->2->3->...
  HIT: SigOut if the trigger hits a full chamber
  MISS: SigOut if the trigger hits a empty chamber
*/
const char desc_variant_3[] =
  "\"VANILLA RESPIN\"\n\n>trigger spins\n cylinder\n>refill and spin on\n last bullet";

/* VARIANT 4
  like vanilla, but after each trigger barrel spins and bullets are not removed
  Encoder works normal
  Step: SigIn advances the cylinder one chamber clockwise
  Trigger: Button/SigIn pulls the trigger and spins it
    BUT: if the last bullet is fired, a bullet is inserted and the cylinder spun
  Spin: Button/SigIn spins the cylinder
  Insert: Button/SigIn inserts/removes a bullet from current chamber
  Add: Button/SigIn adds a chamber to the cylinder 2->3->...->12->2->3->...
  HIT: SigOut if the trigger hits a full chamber
  MISS: SigOut if the trigger hits a empty chamber
*/
const char desc_variant_4[] =
  "\"VANILLA RESPIN\nNO REMOVAL\"\n>trigger spins\n cylinder\n>bullets are not\n removed";

/* VARIANT 5
  Vanilla mode, barrel steps forward after trigger, and inverts current chamber
  Encoder works normal
  Step: SigIn advances the cylinder one chamber clockwise
  Trigger: Button/SigIn pulls the trigger and advances the cylinder one chamber clockwise
    BUT: if the last bullet is fired, a bullet is inserted and the cylinder spun
  Spin: Button/SigIn spins the cylinder
  Insert: Button/SigIn inserts/removes a bullet from current chamber
  Add: Button/SigIn adds a chamber to the cylinder 2->3->...->12->2->3->...
  HIT: SigOut if the trigger hits a full chamber
  MISS: SigOut if the trigger hits a empty chamber
*/
const char desc_variant_5[] =
  "\"INVERT\"\n\n>trigger advances\n cylinder\n>trigger inverts\n chamber";

/* VARIANT 6
  Vanilla mode, barrel spins after trigger, and inverts current chamber a
  Encoder works normal
  Step: SigIn advances the cylinder one chamber clockwise
  Trigger: Button/SigIn pulls the trigger and advances the cylinder one chamber clockwise
    BUT: if the last bullet is fired, a bullet is inserted and the cylinder spun
  Spin: Button/SigIn spins the cylinder
  Insert: Button/SigIn inserts/removes a bullet from current chamber
  Add: Button/SigIn adds a chamber to the cylinder 2->3->...->12->2->3->...
  HIT: SigOut if the trigger hits a full chamber
  MISS: SigOut if the trigger hits a empty chamber
*/
const char desc_variant_6[] =
  "\"INVERT RESPIN\"\n\n>trigger spins\n cylinder\n>trigger inverts\n chamber";

/* VARIANT 7
  Random except 8
*/
const char desc_variant_7[] =
  "\"RANDOM\"\n\n>Behaviour is\n randomly one of the\n 6 previous variants";

/* VARIANT 8
   each trigger fires hit & miss sigout
*/
const char desc_variant_8[] =
  "\"OUTPUT GALORE\"\n\n>trigger outputs on\n HIT and MISS";

//all descriptions of the game variants
const char* desc_variants[]={
  desc_variant_0,
  desc_variant_1,
  desc_variant_2,
  desc_variant_3,
  desc_variant_4,
  desc_variant_5,
  desc_variant_6,
  desc_variant_7,
  desc_variant_8,
};
  
