# Generated by Django 2.0.7 on 2018-08-09 20:22

from django.db import migrations


class Migration(migrations.Migration):

    dependencies = [
        ('infinityroom', '0003_auto_20180808_0025'),
    ]

    operations = [
        migrations.RenameField(
            model_name='globalvars',
            old_name='tcp',
            new_name='tcp_db',
        ),
    ]
