import os

kBuildPathPublicCpp = "../public-cpp/build/"
kBuildPathSegmentor = "segmentor/build/"
kBuildPathNer = "ner/build/"

def call(cmd) :
    assert os.system(cmd) == 0
    
def buildPublicCpp() :
    call("mkdir -p %s && cd %s && cmake ../" % (kBuildPathPublicCpp, kBuildPathPublicCpp))

def buildNer() :
    call("")
    call("cp %s/public-cpp/* ner/deps/public-cpp/" % (kBuildPathPublicCpp, ))
    call("mkdir -p %s && cd %s && cmake ../" % (kBuildPathNer, kBuildPathNer))

if __name__ == "__main__" :    
    buildPublicCpp()
