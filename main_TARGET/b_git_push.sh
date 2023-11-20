cd ./source/common
./b_git_push.sh

cd ../EcuabFee
./b_git_push.sh

cd ../EcuabIfCan
./b_git_push.sh

cd ../EcuabIfMem
./b_git_push.sh

cd ../EcuabTrcvCan
./b_git_push.sh

cd ../LibAutosar
./b_git_push.sh

cd ../McalAdc
./b_git_push.sh

cd ../McalCan
./b_git_push.sh

cd ../McalDio
./b_git_push.sh

cd ../McalFls
./b_git_push.sh

cd ../McalGpt
./b_git_push.sh

cd ../McalLin
./b_git_push.sh

cd ../McalMcu
./b_git_push.sh

cd ../McalWdg
./b_git_push.sh

cd ../ProjectARA
./b_git_push.sh

cd ../ProjectCfg
./b_git_push.sh

cd ../ProjectMemMap
./b_git_push.sh

cd ../SwcApplDcm
./b_git_push.sh

cd ../SwcApplDem
./b_git_push.sh

cd ../SwcApplEcuM
./b_git_push.sh

cd ../SwcApplNvM
./b_git_push.sh

cd ../SwcApplTpms
./b_git_push.sh

cd ../SwcServiceBswM
./b_git_push.sh

cd ../SwcServiceCom
./b_git_push.sh

cd ../SwcServiceComM
./b_git_push.sh

cd ../SwcServiceDcm
./b_git_push.sh

cd ../SwcServiceDem
./b_git_push.sh

cd ../SwcServiceDet
./b_git_push.sh

cd ../SwcServiceEcuM
./b_git_push.sh

cd ../SwcServiceFiM
./b_git_push.sh

cd ../SwcServiceNvM
./b_git_push.sh

cd ../SwcServiceOs
./b_git_push.sh

cd ../SwcServicePduR
./b_git_push.sh

cd ../SwcServiceSchM
./b_git_push.sh

cd ../SwcServiceSmCan
./b_git_push.sh

cd ../SwcServiceStartUp
./b_git_push.sh

cd ../SwcServiceTpCan
./b_git_push.sh

cd ../..
git add .
git status
git commit -m "AUTOSAR Migration Activities - EcuReal_vBcRsBpTpms_TARGET"
git push
