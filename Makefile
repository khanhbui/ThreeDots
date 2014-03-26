keystore:
	keytool -genkey -v -keyalg RSA -keystore bin/release/android/ThreeDots.keystore -alias ThreeDots -validity 10000

sign:
	jarsigner -verbose -sigalg SHA1withRSA -digestalg SHA1 -keystore bin/release/android/ThreeDots.keystore bin/release/android/ThreeDots-release-unsigned.apk ThreeDots

verify:
	jarsigner -verify -verbose -certs bin/release/android/ThreeDots-release-unsigned.apk

zalign:
	zipalign -f -v 4 bin/release/android/ThreeDots-release-unsigned.apk bin/release/android/ThreeDots.apk

compile-release:
	cocos compile -m release -p android -v

compile:
	cocos compile -m debug -p android -v

run:
	cocos run -v -p android

all:
	make compile-release
	make sign
	make verify
	make zalign
