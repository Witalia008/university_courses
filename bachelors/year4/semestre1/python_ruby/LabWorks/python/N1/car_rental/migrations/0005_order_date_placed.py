# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations
import django.utils.timezone


class Migration(migrations.Migration):

    dependencies = [
        ('car_rental', '0004_auto_20151021_1311'),
    ]

    operations = [
        migrations.AddField(
            model_name='order',
            name='date_placed',
            field=models.DateTimeField(default=django.utils.timezone.now),
        ),
    ]
