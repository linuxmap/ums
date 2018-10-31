#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#
#  target compatibility key = gnu.targets.arm.GCArmv7A{1,0,4.3,3
#
ifneq (clean,$(MAKECMDGOALS))
-include package/cfg/81xxApp_xv7A.ov7A.dep
endif

package/cfg/81xxApp_xv7A.ov7A: | .interfaces
package/cfg/81xxApp_xv7A.ov7A: package/cfg/81xxApp_xv7A.c package/cfg/81xxApp_xv7A.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clv7A $< ...
	$(gnu.targets.arm.GCArmv7A.rootDir)/bin/arm-none-linux-gnueabi-gcc -c -MD -MF $@.dep -x c  -fPIC -Wunused -march=armv7-a -Dfar=   -Dxdc_cfg__header__='test_config/package/cfg/81xxApp_xv7A.h'  -Dxdc_target_name__=GCArmv7A -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_3_3 -O2 -ffunction-sections -fdata-sections  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/cfg/81xxApp_xv7A.ov7A:LD_LIBRARY_PATH=

package/cfg/81xxApp_xv7A.sv7A: | .interfaces
package/cfg/81xxApp_xv7A.sv7A: package/cfg/81xxApp_xv7A.c package/cfg/81xxApp_xv7A.mak
	@$(RM) $@.dep
	$(RM) $@
	@$(MSG) clv7A -S $< ...
	$(gnu.targets.arm.GCArmv7A.rootDir)/bin/arm-none-linux-gnueabi-gcc -c -MD -MF $@.dep -x c -S -fPIC -Wunused -march=armv7-a -Dfar=   -Dxdc_cfg__header__='test_config/package/cfg/81xxApp_xv7A.h'  -Dxdc_target_name__=GCArmv7A -Dxdc_target_types__=gnu/targets/arm/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_3_3 -O2 -ffunction-sections -fdata-sections  $(XDCINCS)  -o $@ $<
	-@$(FIXDEP) $@.dep $@.dep
	
package/cfg/81xxApp_xv7A.sv7A:LD_LIBRARY_PATH=

clean,v7A ::
	-$(RM) package/cfg/81xxApp_xv7A.ov7A
	-$(RM) package/cfg/81xxApp_xv7A.sv7A

81xxApp.xv7A: package/cfg/81xxApp_xv7A.ov7A package/cfg/81xxApp_xv7A.mak

clean::
	-$(RM) package/cfg/81xxApp_xv7A.mak
