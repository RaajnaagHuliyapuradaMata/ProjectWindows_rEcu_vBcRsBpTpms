cd ./source/common
./b_git_push.sh

cd ../EcuabCanIf
./b_git_push.sh

cd ../EcuabCanTrcv
./b_git_push.sh

cd ../EcuabFee
./b_git_push.sh

cd ../EcuabMemIf
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

cd ../SwcServiceCanSm
./b_git_push.sh

cd ../SwcServiceCanTp
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

cd ../SwcServiceStartUp
./b_git_push.sh

cd ../..
git add .
git status
git commit -m "AUTOSAR - Hotfixes - pRealEcu_cR_LATEST"
git push
