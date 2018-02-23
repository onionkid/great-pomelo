pipeline 
{

	environment {
		DIR_SRC = '/root/cmake/src'
		DIR_BUILD = '/root/cmake/build'
		APP = './engk'
		DIR_VALGRIND = '/root/cmake/tests/valgrind'
	}

	agent {
	    docker {
	        image 'kevincaballerodico/dockeroo:latest'
	        label 'master'
	        args '-u root'
	    }
	}

    stages {
        stage('Checkout'){
            steps {
                checkout([$class: 'GitSCM', branches: [[name: '*/master']], 
                doGenerateSubmoduleConfigurations: false, 
                extensions: [], 
                submoduleCfg: [], 
                userRemoteConfigs: [[credentialsId: 'github-kiboi', 
                url: 'https://github.com/onionkid/great-pomelo.git']]])
                
                sh 'pwd'
            }
        }
        
        
        stage('Build')
        {
            environment {
				BUILD_GEN   = 'Unix Makefiles'
				BUILD_TYPE  = 'Debug'
			}

			steps {
				sh 'pwd'
			
				sh returnStdout: false, script:
				'''
				cd $WORKSPACE
				cmake --debug-output -G "$BUILD_GEN" -D CMAKE_BUILD_TYPE=$BUILD_TYPE .
				gmake
				'''
			}
        }
    }
}
