#!/bin/bash

basepath=/home/zzj/workspaces/experiment/java
startupScriptName=aahhh


cat > ${basepath}/${startupScriptName}.sh <<EOF
#!/bin/bash

if [ `ps -ef | grep -v grep | grep autostart-test-0.0.1-SNAPSHOT.jar | wc -l` -eq 0 ] ; then
	nohup java -jar ${basepath}/autostart-test-0.0.1-SNAPSHOT.jar > ${basepath}/log.log 2>&1 &
fi

EOF

mv ${basepath}/${startupScriptName}.sh /etc/profile.d/

