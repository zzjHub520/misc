#!/bin/bash

basepath=/home/zzj/workspaces/experiment/java
startupScriptName=aahhh


cat > ${basepath}/${startupScriptName}.sh <<EOF
#!/bin/bash
#chkconfig: 35 20 80
#description: autostart test

nohup /opt/module/jdk/jdk1.8.0_241/bin/java -jar ${basepath}/autostart-test-0.0.1-SNAPSHOT.jar > ${basepath}/logg.log 2>&1 &

EOF

mv ${basepath}/${startupScriptName}.sh /etc/rc.d/init.d/
cd /etc/rc.d/init.d/
chmod +x ${startupScriptName}.sh
chkconfig --add ${startupScriptName}.sh
chkconfig ${startupScriptName}.sh on
