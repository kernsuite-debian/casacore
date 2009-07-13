import os
import sys

EnsureSConsVersion(1,1)

def quiet_print(msg):
    if not GetOption("silent"):
        print msg

env = Environment(ENV = { 'PATH' : os.environ[ 'PATH' ],
			  'HOME' : os.environ[ 'HOME' ] 
			  },
                  tools = ["default", "casaoptions", "buildenv", "casa", "utils",
                           "assaytest", "installer", "dependencies"],
                  toolpath = ["scons-tools"],
                  casashrdir="scons-tools",
		  )
# keep a local sconsign database, rather than in very directory
env.SConsignFile()

AddOption("--enable-hdf5", dest="enable_hdf5",
          action="store_true", default=False)
AddOption("--disable-dl", dest="disable_dl",
          action="store_true", default=False)
AddOption("--disable-static", dest="disable_static",
          action="store_true", default=False)
AddOption("--enable-shared", dest="enable_shared",
          action="store_true", default=False)

env.AddPkgOptions("hdf5")
env.AddPkgOptions("dl")
env.AddPkgOptions("blas")
env.AddPkgOptions("lapack")
env.AddPkgOptions("f2c", lib="gfortran")


env["build"]=["opt"]

if not (env.Detect(["flex","lex"]) and env.Detect(["bison", "yacc"])):
    print "lex/yacc needs to be installed"
    env.Exit(1)

# Auto configure
if not env.GetOption('clean') and not env.GetOption("help"):
    conf = Configure(env)
    # test for blas/lapack
    conf.env.CheckFortran(conf)

    f2cname = conf.env.get("f2c_lib", conf.env["F2CLIB"])
    conf.env.AddCustomPackage("f2c")
    if not conf.CheckLib(f2cname, autoadd=0):
        Exit(1)

    blasname = conf.env.get("blas_lib", "blas").split(",")
    conf.env.AddCustomPackage("blas")
    blasname.reverse()
    for b in blasname:
        if not conf.CheckLib(b, autoadd=0):
            Exit(1)
    conf.env["BLAS"] = blasname            
    lapackname = conf.env.get("lapack_lib", "lapack").split(",")
    conf.env.AddCustomPackage("lapack")
    lapackname.reverse()
    for l in lapackname:
        if not conf.CheckLib(l, autoadd=0):
            Exit(1)
    conf.env["LAPACK"] = lapackname
    # HDF5
    if conf.env.GetOption("enable_hdf5"):
        pkgname = "hdf5"
        libname = conf.env.get(pkgname+"_lib")
        conf.env.AddCustomPackage(pkgname)
        if conf.CheckLib(libname, autoadd=0):
            conf.env.PrependUnique(LIBS=[libname])
            conf.env.Append(CPPFLAGS=['-DHAVE_LIBHDF5'])
        else:
            env.Exit(1)
    else:
        quiet_print("Building without HDF5 support")
    # DL
    if not conf.env.GetOption("disable_dl"):
        pkgname = "dl"
        libname = env.get(pkgname+"_lib")
        conf.env.AddCustomPackage(pkgname)
        if conf.CheckLibWithHeader(libname, 'dlfcn.h', language='c', autoadd=0):
            conf.env.AppendUnique(LIBS=[libname])
            conf.env.Append(CPPFLAGS=['-DHAVE_DLOPEN'])
        else:
            env.Exit(1)
    else:
        print "Building without dlopen support"    

    env = conf.Finish()
else:
    env.Execute(Delete("options.cfg"))
# create the installer which handles installing the final build
installer = env.Installer()

# to find package based includes
env.Append(CPPPATH='#')

for bopt in env["build"]:
    # create an environment copy with the dbg/opt compiler flags
    buildenv = env.BuildEnv(bopt)
    # buildir name
    buildenv["BUILDDIR"] = Dir("#/build_%s/%s" % (env.PlatformIdent(), bopt))
    buildenv.PrependUnique(LIBPATH=[buildenv["BUILDDIR"]])    
    env.SConscript("SConscript" , 
		   build_dir= buildenv["BUILDDIR"],
		   duplicate=0, exports=["buildenv", "installer"])

# add the Tools to the casacore/share directory. This way they can be imported
# by the other casacore packages without having to duplicate them.
installer.AddShares("scons-tools", "*.py", "casacore/", True)
installer.AddShares("scons-tools", "casacore_assay", "casacore/")
installer.AddShares("scons-tools", "floatcheck.sh", "casacore/")
