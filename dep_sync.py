import os, sys

kBuildPathPublicCpp = "../public-cpp/build/"

kBuildPathNer = "ner/build/"
kBuildPathSegmentor = "segmentor/build/"
kBuildPathCharles = "charles/build/"

kDepPathNer = "ner/deps/"
kDepPathSegmentor = "segmentor/deps/"
kDepPathCharles = "charles/deps/"

def call(cmd) :
    assert os.system(cmd) == 0
    
def buildPublicCpp() :
    call("mkdir -p %s && cd %s && cmake ../ && make clean && make -j4 -s" % \
            (kBuildPathPublicCpp, kBuildPathPublicCpp))

def buildNer() :
    call("mkdir -p %s && rm -rf %s/*" % (kDepPathNer, kDepPathNer))
    call("cp -rf %s/public-cpp %s/public-cpp" % \
            (kBuildPathPublicCpp, kDepPathNer))
    call("mkdir -p %s && cd %s && cmake ../ && make clean && make -j4 -s" % \
            (kBuildPathNer, kBuildPathNer))

def buildSegmentor() :    
    call("mkdir -p %s && rm -rf %s/*" % (kDepPathSegmentor, kDepPathSegmentor))
    call("cp -rf %s/public-cpp %s/public-cpp" % \
            (kBuildPathPublicCpp, kDepPathSegmentor))
    call("cp -rf %s/ner %s/ner" % \
            (kBuildPathNer, kDepPathSegmentor))
    call("mkdir -p %s && cd %s && cmake ../ && make clean && make -j4 -s" % \
            (kBuildPathSegmentor, kBuildPathSegmentor))

def buildCharles() :
    call("mkdir -p %s && rm -rf %s/*" % (kDepPathCharles, kDepPathCharles))
    call("cp -rf %s/public-cpp %s/public-cpp/" % \
            (kBuildPathPublicCpp, kDepPathCharles))
    call("cp -rf %s/ner %s/ner/" % \
            (kBuildPathNer, kDepPathCharles))
    call("cp -rf %s/segmentor %s/segmentor" % \
            (kBuildPathSegmentor, kDepPathCharles))
    call("mkdir -p %s && cd %s && cmake ../ && make clean && make -j4 -s" % \
            (kBuildPathCharles, kBuildPathCharles))


if __name__ == "__main__" :    
    if len(sys.argv) < 2 :
        print("invalid syntax, no args")
        sys.exit(1)

    buildPublicCpp()
    if sys.argv[1] == "pub" :
        sys.exit(0)

    buildNer()
    if sys.argv[1] == "ner" :
        sys.exit(0)

    buildSegmentor()
    if sys.argv[1] == "seg" :
        sys.exit(0)

    buildCharles()
    if sys.argv[1] == "chr" :
        sys.exit(0)
    else :
        print("unknown mod[%s]" % sys.argv[1])
        sys.exit(2)
