pipeline 
{

	environment {
		//DIR_SRC = '/root/cmake/src'
		//DIR_BUILD = '/root/cmake/build'
		APP = './greatPomelo'
		DIR_VALGRIND = $WORKSPACE/valgrind'
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
        
        stage('Valgrind Prepare')
        {
        	steps {
        		sh returnStdout: false, script: 
        		'''
        		mkdir $DIR_VALGRIND
        		'''
        	}
        }
        
		stage('Static Analysis') {
			parallel {
				stage('VALGRIND MEMCHECK') {
				    steps {
				    	sh returnStdout: false, script:
						'''
						cd $DIR_BUILD
						valgrind --tool=memcheck \
						--xml=yes \
						--xml-file=$DIR_VALGRIND/memcheck.xml \
						--log-file=$DIR_VALGRIND/memcheck.log \
						$APP
						'''
				    }
		    	}

				stage('VALGRIND HELGRIND') {
					steps {
						sh returnStdout: false, script: 
						'''
						cd $DIR_BUILD
						valgrind --tool=helgrind \
						--xml=yes \
						--xml-file=$DIR_VALGRIND/helgrind.xml \
						--log-file=$DIR_VALGRIND/helgrind.log \
						$APP
						'''
					}
				}

				stage('VALGRIND DRD') {
					steps {
						sh returnStdout: false, script: 
						'''
						cd $DIR_BUILD
						valgrind --tool=drd \
						--xml=yes \
						--xml-file=$DIR_VALGRIND/drd.xml \
						--log-file=$DIR_VALGRIND/drd.log \
						$APP
						'''
					}
				}

				stage('VALGRIND CACHEGRIND') {
					steps {
						sh returnStdout: false, script: 
						'''
						cd $DIR_BUILD
						valgrind --tool=cachegrind \
						--cachegrind-out-file=$DIR_VALGRIND/cachegrind.txt \
						--log-file=$DIR_VALGRIND/cachegrind.log \
						$APP
						'''
					}
				}

				stage('VALGRIND CALLGRIND') {
					steps {
						sh returnStdout: false, script: 
						'''
						cd $DIR_BUILD
						valgrind --tool=callgrind \
						--callgrind-out-file=$DIR_VALGRIND/callgrind.txt \
						--log-file=$DIR_VALGRIND/callgrind.log \
						$APP
						'''
					}
				}

				stage('VALGRIND MASSIF') {
					steps {
						sh returnStdout: false, script: 
						'''
						cd $DIR_BUILD
						valgrind --tool=massif \
						--massif-out-file=$DIR_VALGRIND/massif.txt \
						--log-file=$DIR_VALGRIND/massif.log \
						$APP
						'''
					}
				}

				stage('VALGRIND LACKEY') {
					steps {
						sh returnStdout: false, script: 
						'''
						cd $DIR_BUILD
						valgrind --tool=lackey \
						--log-file=$DIR_VALGRIND/lackey.log \
						$APP
						'''
					}
				}
			}

			post {
				success {
					sh returnStdout: false, script: 
					'''
					pwd
					tree $WORKSPACE
					'''
					//artifactoryUpload spec: "spec", buildInfo: "buildinfo", server: 'dockeroo'
				}
			}
		}
    }
}
