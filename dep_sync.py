import os, sys

kBuildPathPublicCpp = "../public-cpp/build/"

kBuildPathBasic = "basic/build/"
kBuildPathMilkie = "milkie/build/"
kBuildPathNer = "ner/build/"
kBuildPathSegmentor = "segmentor/build/"
kBuildPathPosTagging = "pos_tagging/build/"
kBuildPathChunker = "chunker/build/"
kBuildPathCharles = "charles/build/"

kDepPathBasic = "basic/deps/"
kDepPathMilkie = "milkie/deps/"
kDepPathNer = "ner/deps/"
kDepPathSegmentor = "segmentor/deps/"
kDepPathPosTagging = "pos_tagging/deps/"
kDepPathChunker = "chunker/deps/"
kDepPathCharles = "charles/deps/"

def call(cmd) :
    assert os.system(cmd) == 0
    
def buildPublicCpp() :
    call("mkdir -p %s && cd %s && cmake ../ && make clean && make -j4 -s" % \
            (kBuildPathPublicCpp, kBuildPathPublicCpp))

def buildBasic() :
    call("mkdir -p %s && rm -rf %s/*" % (kDepPathBasic, kDepPathBasic))
    call("cp -rf %s/public-cpp %s/public-cpp" % \
            (kBuildPathPublicCpp, kDepPathBasic))
    call("mkdir -p %s && cd %s && cmake ../ && make clean && make -j4 -s" % \
            (kBuildPathBasic, kBuildPathBasic))

def buildMilkie() :
    call("mkdir -p %s && rm -rf %s/*" % (kDepPathMilkie, kDepPathMilkie))
    call("cp -rf %s/public-cpp %s/public-cpp" % \
            (kBuildPathPublicCpp, kDepPathMilkie))
    call("cp -rf %s/basic %s/basic" % \
            (kBuildPathBasic, kDepPathMilkie))
    call("mkdir -p %s && cd %s && cmake ../ && make clean && make -j4 -s" % \
            (kBuildPathMilkie, kBuildPathMilkie))

def buildPosTagging() :
    call("mkdir -p %s && rm -rf %s/*" % (kDepPathPosTagging, kDepPathPosTagging))
    call("cp -rf %s/public-cpp %s/public-cpp" % \
            (kBuildPathPublicCpp, kDepPathPosTagging))
    call("cp -rf %s/basic %s/basic/" % \
            (kBuildPathBasic, kDepPathPosTagging))
    call("cp -rf %s/ner %s/ner/" % \
            (kBuildPathNer, kDepPathPosTagging))
    call("cp -rf %s/segmentor %s/segmentor/" % \
            (kBuildPathSegmentor, kDepPathPosTagging))
    call("mkdir -p %s && cd %s && cmake ../ && make clean && make -j4 -s" % \
            (kBuildPathPosTagging, kBuildPathPosTagging))

def buildNer() :
    call("mkdir -p %s && rm -rf %s/*" % (kDepPathNer, kDepPathNer))
    call("cp -rf %s/public-cpp %s/public-cpp" % \
            (kBuildPathPublicCpp, kDepPathNer))
    call("cp -rf %s/basic %s/basic" % \
            (kBuildPathBasic, kDepPathNer))
    call("mkdir -p %s && cd %s && cmake ../ && make clean && make -j4 -s" % \
            (kBuildPathNer, kBuildPathNer))

def buildSegmentor() :    
    call("mkdir -p %s && rm -rf %s/*" % (kDepPathSegmentor, kDepPathSegmentor))
    call("cp -rf %s/public-cpp %s/public-cpp" % \
            (kBuildPathPublicCpp, kDepPathSegmentor))
    call("cp -rf %s/basic %s/basic" % \
            (kBuildPathBasic, kDepPathSegmentor))
    call("cp -rf %s/ner %s/ner" % \
            (kBuildPathNer, kDepPathSegmentor))
    call("mkdir -p %s && cd %s && cmake ../ && make clean && make -j4 -s" % \
            (kBuildPathSegmentor, kBuildPathSegmentor))

def buildChunker() :
    call("mkdir -p %s && rm -rf %s/*" % (kDepPathChunker, kDepPathChunker))
    call("cp -rf %s/public-cpp %s/public-cpp" % \
            (kBuildPathPublicCpp, kDepPathChunker))
    call("cp -rf %s/basic %s/basic/" % \
            (kBuildPathBasic, kDepPathChunker))
    call("cp -rf %s/milkie %s/milkie/" % \
            (kBuildPathMilkie, kDepPathChunker))
    call("mkdir -p %s && cd %s && cmake ../ && make clean && make -j4 -s" % \
            (kBuildPathChunker, kBuildPathChunker))

def buildCharles() :
    call("mkdir -p %s && rm -rf %s/*" % (kDepPathCharles, kDepPathCharles))
    call("cp -rf %s/public-cpp %s/public-cpp/" % \
            (kBuildPathPublicCpp, kDepPathCharles))
    call("cp -rf %s/basic %s/basic/" % \
            (kBuildPathBasic, kDepPathCharles))
    call("cp -rf %s/ner %s/ner/" % \
            (kBuildPathNer, kDepPathCharles))
    call("cp -rf %s/segmentor %s/segmentor/" % \
            (kBuildPathSegmentor, kDepPathCharles))
    call("cp -rf %s/pos_tagging %s/pos_tagging/" % \
            (kBuildPathPosTagging, kDepPathCharles))
    call("mkdir -p %s && cd %s && cmake ../ && make clean && make -j4 -s" % \
            (kBuildPathCharles, kBuildPathCharles))

if __name__ == "__main__" :    
    if len(sys.argv) < 2 :
        print("invalid syntax, no args")
        sys.exit(1)

    buildPublicCpp()
    if sys.argv[1] == "pub" :
        sys.exit(0)

    buildBasic()
    if sys.argv[1] == "bas" :
        sys.exit(0)

    buildMilkie()
    if sys.argv[1] == "mki" :
        sys.exit(0)

    buildNer()
    if sys.argv[1] == "ner" :
        sys.exit(0)

    buildSegmentor()
    if sys.argv[1] == "seg" :
        sys.exit(0)

    buildPosTagging()
    if sys.argv[1] == "pos" :
        sys.exit(0)

    buildChunker()
    if sys.argv[1] == "chk" :
        sys.exit(0)

    buildCharles()
    if sys.argv[1] == "chr" :
        sys.exit(0)
    else :
        print("unknown mod[%s]" % sys.argv[1])
        sys.exit(2)
