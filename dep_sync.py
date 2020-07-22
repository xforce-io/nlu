import os, sys

kBuildPathPublicCpp = "../public-cpp/build/"

kBuildPathBasic = "basic/build/"
kBuildPathMilkie = "milkie/build/"
kBuildPathNer = "ner/build/"
kBuildPathSegmentor = "segmentor/build/"
kBuildPathPosTagging = "pos_tagging/build/"
kBuildPathChunker = "chunker/build/"
kBuildPathSyntax = "syntax/build/"
kBuildPathSemantic = "semantic/build/"
kBuildPathCharles = "charles/build/"

kDepPathBasic = "basic/deps/"
kDepPathMilkie = "milkie/deps/"
kDepPathNer = "ner/deps/"
kDepPathSegmentor = "segmentor/deps/"
kDepPathPosTagging = "pos_tagging/deps/"
kDepPathChunker = "chunker/deps/"
kDepPathSyntax= "syntax/deps/"
kDepPathSemantic = "semantic/deps/"
kDepPathCharles = "charles/deps/"

def call(cmd) :
    assert os.system(cmd) == 0
    
def buildPublicCpp() :
    call("mkdir -p %s && rm -rf %s/* && cd %s && cmake ../ && make clean && make -j4 -s" % \
            (kBuildPathPublicCpp, kBuildPathPublicCpp, kBuildPathPublicCpp))

def buildBasic() :
    call("mkdir -p %s && rm -rf %s/*" % (kDepPathBasic, kDepPathBasic))
    call("cp -rf %s/public-cpp %s/public-cpp" % \
            (kBuildPathPublicCpp, kDepPathBasic))
    call("mkdir -p %s && rm -rf %s/* && cd %s && cmake ../ && make clean && make -j4 -s" % \
            (kBuildPathBasic, kBuildPathBasic, kBuildPathBasic))

def buildMilkie() :
    call("mkdir -p %s && rm -rf %s/*" % (kDepPathMilkie, kDepPathMilkie))
    call("cp -rf %s/public-cpp %s/public-cpp" % \
            (kBuildPathPublicCpp, kDepPathMilkie))
    call("cp -rf %s/basic %s/basic" % \
            (kBuildPathBasic, kDepPathMilkie))
    call("mkdir -p %s && rm -rf %s/* && cd %s && cmake ../ && make clean && make -j4 -s" % \
            (kBuildPathMilkie, kBuildPathMilkie, kBuildPathMilkie))

def buildNer() :
    call("mkdir -p %s && rm -rf %s/*" % (kDepPathNer, kDepPathNer))
    call("cp -rf %s/public-cpp %s/public-cpp" % \
            (kBuildPathPublicCpp, kDepPathNer))
    call("cp -rf %s/basic %s/basic" % \
            (kBuildPathBasic, kDepPathNer))
    call("mkdir -p %s && rm -rf %s/* && cd %s && cmake ../ && make clean && make -j4 -s" % \
            (kBuildPathNer, kBuildPathNer, kBuildPathNer))

def buildSegmentor() :    
    call("mkdir -p %s && rm -rf %s/*" % (kDepPathSegmentor, kDepPathSegmentor))
    call("cp -rf %s/public-cpp %s/public-cpp" % \
            (kBuildPathPublicCpp, kDepPathSegmentor))
    call("cp -rf %s/basic %s/basic" % \
            (kBuildPathBasic, kDepPathSegmentor))
    call("cp -rf %s/ner %s/ner" % \
            (kBuildPathNer, kDepPathSegmentor))
    call("mkdir -p %s && rm -rf %s/* && cd %s && cmake ../ && make clean && make -j4 -s" % \
            (kBuildPathSegmentor, kBuildPathSegmentor, kBuildPathSegmentor))

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
    call("mkdir -p %s && rm -rf %s/* && cd %s && cmake ../ && make clean && make -j4 -s" % \
            (kBuildPathPosTagging, kBuildPathPosTagging, kBuildPathPosTagging))

def buildChunker() :
    call("mkdir -p %s && rm -rf %s/*" % (kDepPathChunker, kDepPathChunker))
    call("cp -rf %s/public-cpp %s/public-cpp" % \
            (kBuildPathPublicCpp, kDepPathChunker))
    call("cp -rf %s/basic %s/basic/" % \
            (kBuildPathBasic, kDepPathChunker))
    call("cp -rf %s/milkie %s/milkie/" % \
            (kBuildPathMilkie, kDepPathChunker))
    call("cp -rf %s/ner %s/ner/" % \
            (kBuildPathNer, kDepPathChunker))
    call("cp -rf %s/segmentor %s/segmentor/" % \
            (kBuildPathSegmentor, kDepPathChunker))
    call("cp -rf %s/pos_tagging %s/pos_tagging/" % \
            (kBuildPathPosTagging, kDepPathChunker))
    call("mkdir -p %s && rm -rf %s/* && cd %s && cmake ../ && make clean && make -j4 -s" % \
            (kBuildPathChunker, kBuildPathChunker, kBuildPathChunker))

def buildSyntax() :
    call("mkdir -p %s && rm -rf %s/*" % (kDepPathSyntax, kDepPathSyntax))
    call("cp -rf %s/public-cpp %s/public-cpp" % \
            (kBuildPathPublicCpp, kDepPathSyntax))
    call("cp -rf %s/basic %s/basic/" % \
            (kBuildPathBasic, kDepPathSyntax))
    call("cp -rf %s/milkie %s/milkie/" % \
            (kBuildPathMilkie, kDepPathSyntax))
    call("cp -rf %s/ner %s/ner/" % \
            (kBuildPathNer, kDepPathSyntax))
    call("cp -rf %s/segmentor %s/segmentor/" % \
            (kBuildPathSegmentor, kDepPathSyntax))
    call("cp -rf %s/pos_tagging %s/pos_tagging/" % \
            (kBuildPathPosTagging, kDepPathSyntax))
    call("cp -rf %s/chunker %s/chunker/" % \
            (kBuildPathChunker, kDepPathSyntax))
    call("mkdir -p %s && rm -rf %s/* && cd %s && cmake ../ && make clean && make -j4 -s" % \
            (kBuildPathSyntax, kBuildPathSyntax, kBuildPathSyntax))

def buildSemantic() :
    call("mkdir -p %s && rm -rf %s/*" % (kDepPathSemantic, kDepPathSemantic))
    call("cp -rf %s/public-cpp %s/public-cpp" % \
            (kBuildPathPublicCpp, kDepPathSemantic))
    call("cp -rf %s/basic %s/basic/" % \
            (kBuildPathBasic, kDepPathSemantic))
    call("cp -rf %s/milkie %s/milkie/" % \
            (kBuildPathMilkie, kDepPathSemantic))
    call("cp -rf %s/ner %s/ner/" % \
            (kBuildPathNer, kDepPathSemantic))
    call("cp -rf %s/segmentor %s/segmentor/" % \
            (kBuildPathSegmentor, kDepPathSemantic))
    call("cp -rf %s/pos_tagging %s/pos_tagging/" % \
            (kBuildPathPosTagging, kDepPathSemantic))
    call("cp -rf %s/chunker %s/chunker/" % \
            (kBuildPathChunker, kDepPathSemantic))
    call("cp -rf %s/syntax %s/syntax/" % \
            (kBuildPathSyntax, kDepPathSemantic))
    call("mkdir -p %s && rm -rf %s/* && cd %s && cmake ../ && make clean && make -j4 -s" % \
            (kBuildPathSemantic, kBuildPathSemantic, kBuildPathSemantic))

def buildCharles() :
    call("mkdir -p %s && rm -rf %s/*" % (kDepPathCharles, kDepPathCharles))
    call("cp -rf %s/public-cpp %s/public-cpp/" % \
            (kBuildPathPublicCpp, kDepPathCharles))
    call("cp -rf %s/basic %s/basic/" % \
            (kBuildPathBasic, kDepPathCharles))
    call("cp -rf %s/milkie %s/milkie/" % \
            (kBuildPathMilkie, kDepPathCharles))
    call("cp -rf %s/ner %s/ner/" % \
            (kBuildPathNer, kDepPathCharles))
    call("cp -rf %s/segmentor %s/segmentor/" % \
            (kBuildPathSegmentor, kDepPathCharles))
    call("cp -rf %s/pos_tagging %s/pos_tagging/" % \
            (kBuildPathPosTagging, kDepPathCharles))
    call("cp -rf %s/chunker %s/chunker/" % \
            (kBuildPathChunker, kDepPathCharles))
    call("cp -rf %s/syntax %s/syntax/" % \
            (kBuildPathSyntax, kDepPathCharles))
    call("cp -rf %s/semantic %s/semantic/" % \
            (kBuildPathSemantic, kDepPathCharles))
    call("mkdir -p %s && rm -rf %s/* && cd %s && cmake ../ && make clean && make -j4 -s" % \
            (kBuildPathCharles, kBuildPathCharles, kBuildPathCharles))

if __name__ == "__main__" :    
    if len(sys.argv) < 2 :
        print("invalid syntax, no args")
        sys.exit(1)

    if len(sys.argv) == 2 :
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

        buildSyntax()
        if sys.argv[1] == "syn" :
            sys.exit(0)

        buildSemantic()
        if sys.argv[1] == "sem" :
            sys.exit(0)

        buildCharles()
        if sys.argv[1] == "chr" :
            sys.exit(0)
        else :
            print("unknown mod[%s]" % sys.argv[1])
            sys.exit(2)
    elif len(sys.argv) == 3 and sys.argv[2] == "f" :
        if sys.argv[1] == "mki" :
            buildMilkie()
            buildNer()
            buildSegmentor()
            buildPosTagging()
            buildChunker()
            buildSyntax()
            buildSemantic()
            buildCharles()        
        elif sys.argv[1] == "pos" :
            buildPosTagging()
            buildChunker()
            buildSyntax()
            buildSemantic()
            buildCharles()
        elif sys.argv[1] == "chk" :    
            buildChunker()
            buildSyntax()
            buildSemantic()
            buildCharles()
        elif sys.argv[1] == "syn" :
            buildSyntax()
            buildSemantic()
            buildCharles()
        elif sys.argv[1] == "sem" :
            buildSemantic()
            buildCharles()
        else :    
            print("unknown mod[%s]" % sys.argv[1])
            sys.exit(3)
