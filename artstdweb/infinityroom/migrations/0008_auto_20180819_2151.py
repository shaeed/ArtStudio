# Generated by Django 2.1 on 2018-08-19 16:21

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('infinityroom', '0007_auto_20180819_1953'),
    ]

    operations = [
        migrations.AlterField(
            model_name='settings',
            name='sys_ip_db',
            field=models.CharField(max_length=99999),
        ),
    ]
