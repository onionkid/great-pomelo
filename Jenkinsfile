pipeline 
{

	environment {
		APP = './greatPomelo'
		APP_TEST = './greatPomeloTest'
		DIR_VALGRIND = 'valgrind'
		DIR_BUILD = "$WORKSPACE"
		SERVER_ID = 'dockeroo'
	}

	agent {
	    docker {
	        image 'kiboi/dockeroo-ut:ver1'
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
            }
        }
               
        stage('Build')
        {
            environment {
				BUILD_GEN   = 'Unix Makefiles'
				BUILD_TYPE  = 'Debug'
			}

			steps {
				sh returnStdout: false, script:
				'''
				cd $WORKSPACE
				cmake --debug-output -G "$BUILD_GEN" -D CMAKE_BUILD_TYPE=$BUILD_TYPE .
				gmake
				'''
			}
        }
		
		stage('CUnit Test')
        {
        	steps {
				sh returnStdout: false, script:
				'''
				cd $WORKSPACE
				$APP_TEST
				'''
			}
        }
		       
        stage('Valgrind Prepare')
        {
        	steps {
        		sh returnStdout: false, script: 
        		'''
        		cd $WORKSPACE
				rm -rf valgrind
        		mkdir valgrind
        		'''
        	}
        }
		
		stage('Static Analysis') {
			parallel {
				stage('VALGRIND MEMCHECK') {
				    steps {
				    	sh returnStdout: false, script:
						'''
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
						valgrind --tool=helgrind \
						--xml=yes \
						--xml-file=$DIR_VALGRIND/helgrind.xml \
						--log-file=$DIR_VALGRIND/helgrind.log \
						$APP
						'''
					}
				}
				
				stage('VALGRIND CACHEGRIND') {
					steps {
						sh returnStdout: false, script: 
						'''
						valgrind --tool=cachegrind \
						--cachegrind-out-file=$DIR_VALGRIND/cachegrind.txt \
						--log-file=$DIR_VALGRIND/cachegrind.log \
						$APP
						'''
					}
				}
			}
		}
        		
		stage('Archive Artifacts')
        {
        	steps {
        		sh returnStdout: false, script: 
        		'''
        		cd $WORKSPACE
        		'''
				
				archiveArtifacts artifacts: 'greatPomelo', fingerprint: true, onlyIfSuccessful: true
				archiveArtifacts artifacts: 'libfoo.a', fingerprint: true, onlyIfSuccessful: true
				archiveArtifacts artifacts: 'libhoot.a', fingerprint: true, onlyIfSuccessful: true
				
				script {
					def server = Artifactory.server 'dockeroo'
					def uploadSpec = '''{
					  "files": [
						{
						  "pattern": "libfoo*.a",
						  "target": "generic-local/libfoo/"
						},
						{
						  "pattern": "libhoot*.a",
						  "target": "generic-local/libhoot/"
						},
						{
						  "pattern": "greatPomelo",
						  "target": "generic-local/greatPomelo/"
						}

					 ]
					}'''
					server.upload(uploadSpec)
				}
        	}
        
		
			post{
				always{
			
					//emailext body: 'Hello!', recipientProviders: [[$class: 'RequesterRecipientProvider']], subject: 'ASD', to: 'kevinarnado@gmail.com'
                    echo "Job Complete!"
				}
			}
		}
    }
}
