source ./exportVariables.sh

cd $JETSON_KERNEL_SOURCE
make ARCH=arm64 CROSS_COMPILE=$CROSS_COMPILER O=$JETSON_KERNEL_OUT -j4
sudo make ARCH=arm64 CROSS_COMPILE=$CROSS_COMPILER O=$JETSON_KERNEL_OUT modules_install INSTALL_MOD_PATH=$JETSON_KERNEL_MODULE_OUT
