pipeline 
{
    agent any
    stages {
        stage('Checkout'){
            steps {
                checkout([$class: 'GitSCM', branches: [[name: '*/master']], 
                doGenerateSubmoduleConfigurations: false, 
                extensions: [], 
                submoduleCfg: [], 
                userRemoteConfigs: [[credentialsId: 'github-kiboi', 
                url: 'https://github.com/onionkid/great-pomelo.git']]])
            }
        }
        
        stage('Build')
        {
            environment {
				BUILD_GEN   = 'Unix Makefiles'
				BUILD_TYPE  = 'Debug'
				BUILD_CMAKE = '/var/lib/cmake-3.10.2/bin/cmake'
				BUILD_GMAKE = '/bin/gmake'
			}

			steps {
				sh returnStdout: false, script:
				'''
				cd $WORKSPACE
				$BUILD_CMAKE --debug-output -G "$BUILD_GEN" -D CMAKE_BUILD_TYPE=$BUILD_TYPE .
				$BUILD_GMAKE
				'''
			}
        }
    }
}
