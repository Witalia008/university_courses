from django.db import models

# Create your models here.
from django.utils import timezone


class Course(models.Model):
    courseName = models.CharField(max_length=200)
    opened = models.BooleanField(default=False)
    startDate = models.DateTimeField(default=timezone.now)
    endDate = models.DateTimeField(default=timezone.now)
    students = models.ManyToManyField('auth.User', related_name='course_students')
    teachers = models.ManyToManyField('auth.User', related_name='course_teachers')

    def __unicode__(self):
        return self.courseName

    def signup(self, user):
        self.students.add(user)
        self.save()


class Mark(models.Model):
    value = models.IntegerField(default=0)
    course = models.ForeignKey(Course, related_name='mark_course')
    student = models.ForeignKey('auth.User', related_name='mark_student')
    teacher = models.ForeignKey('auth.User', related_name='mark_teacher')

    def __unicode__(self):
        return "(%s, %s - %s)" % (str(self.student), str(self.course), str(self.value))


# def signup(self, user):
#     self.students.add(user)
#     self.save()
#
# Course = type('Course', (models.Model,), {
#     'courseName': models.CharField(max_length=200),
#     'opened': models.BooleanField(default=False),
#     'startDate': models.DateTimeField(default=timezone.now),
#     'endDate': models.DateTimeField(default=timezone.now),
#     'students': models.ManyToManyField('auth.User', related_name='course_students'),
#     'teachers': models.ManyToManyField('auth.User', related_name='course_teachers'),
#
#     '__unicode__': lambda self: self.courseName,
#     'signup': signup,
#
#     '__module__': __name__,
# })
#
#
# Mark = type('Mark', (models.Model,), {
#     'value': models.IntegerField(default=0),
#     'course': models.ForeignKey(Course, related_name='mark_course'),
#     'student': models.ForeignKey('auth.User', related_name='mark_student'),
#     'teacher': models.ForeignKey('auth.User', related_name='mark_teacher'),
#
#     '__unicode__': lambda self: "(%s, %s - %s)" % (str(self.student), str(self.course), str(self.value)),
#     '__module__': __name__,
# })
