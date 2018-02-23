pipeline 
{

	environment {
		APP = './greatPomelo'
		DIR_VALGRIND = 'valgrind'
		DIR_BUILD = "$WORKSPACE"
		SERVER_ID = 'dockeroo'
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
						cd $WORKSPACE
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
						cd $WORKSPACE
						valgrind --tool=helgrind \
						--xml=yes \
						--xml-file=$DIR_VALGRIND/helgrind.xml \
						--log-file=$DIR_VALGRIND/helgrind.log \
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
				
				script {
					def server = Artifactory.server 'dockeroo'
					def uploadSpec = '''{
					  "files": [
						{
						  "pattern": "libfoo*.a",
						  "target": "generic-local/libfoo/"
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
			
					emailext body: 'Hello!', recipientProviders: [[$class: 'RequesterRecipientProvider']], subject: 'ASD', to: 'kevinarnado@gmail.com'

				}
			}
		}
    }
}
