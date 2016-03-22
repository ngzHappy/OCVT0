
CONFIG(debug,debug|release){

}else{
DEFINES *= NDEBUG
}

INCLUDEPATH += $$PWD
include( $$PWD/opencv3.pri )

win32 :{
DEFINES += LOCAL_CODEC_=\\\"GBK\\\"
}else{
DEFINES += LOCAL_CODEC_=\\\"UTF-8\\\"
}

win32{

win32-msvc*{

CONFIG(debug,debug|release){
OUTPWD=$$clean_path( $$PWD/../binlib/msvc/bind )
}else{
OUTPWD=$$clean_path( $$PWD/../binlib/msvc/bin )
}

}else{

CONFIG(debug,debug|release){
OUTPWD=$$clean_path( $$PWD/../binlib/win32/bind )
}else{
OUTPWD=$$clean_path( $$PWD/../binlib/win32/bin )
}

}

}else{

CONFIG(debug,debug|release){
OUTPWD=$$clean_path( $$PWD/../binlib/common/bind )
}else{
OUTPWD=$$clean_path( $$PWD/../binlib/common/bin )
}

}


